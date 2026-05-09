//
// Created by Andrey Baryshev on 05.05.2026.
//
#include "sync_handler.h"
#include "nlohmann/json.hpp"
#include "../server/Router.h"
#include "../config/Config.h"
#include "../utils/logger/Logger.h"
#include<fstream>
#include<iomanip>
#include<vector>
#include<openssl/md5.h>

nlohmann::json getUpgradeFiles(const nlohmann::json& files);
std::string getFileHash(const std::string& filename);

void handleSync(const HttpRequest &req, HttpResponse &res) {
    try {
        nlohmann::json userJson = nlohmann::json::parse(req.body());

        if (!userJson.contains("files") || !userJson["files"].is_object()) {
            nlohmann::json errorJson;
            errorJson["error"] = "Required field \"files\" with filename with hash";

            res.body() = errorJson.dump();
            res.result(http::status::bad_request);
            return;
        }

        nlohmann::json resJson = getUpgradeFiles(userJson["files"]);

        res.body() = resJson.dump();
        res.result(http::status::ok);

    } catch (std::exception& ex) {
        Logger::error("Failed to send response (/sync): {}", ex.what());

        nlohmann::json errorJson;
        errorJson["error"] = "Internal server error";
        res.body() = errorJson.dump();
        res.result(http::status::internal_server_error);
    }
}

nlohmann::json getUpgradeFiles(const nlohmann::json& files) {
    nlohmann::json response{};

    response["files"] = nlohmann::json::array();
    response["to_delete"] = nlohmann::json::array();
    for (auto& [filename, client_hash] : files.items()) {
        if (!Config::getInstance().shouldSendToClient(filename)) {
            response["to_delete"].push_back(filename);
        }

        std::string file_hash = getFileHash(filename);

        Logger::debug("Checking: {} (client: {} vs server: {})", filename, client_hash.get<std::string>(), file_hash);

        if (client_hash != file_hash) {
            response["files"].push_back(filename);
            Logger::debug("Will update: {}", filename);
        }
    }

    return response;
}

std::string getFileHash(const std::string& filename) {
    std::string modsDir = Config::getInstance().getModsDir();
    std::string fullPath = modsDir + "/" + filename;

    std::ifstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        Logger::error("Failed to open file: {}", fullPath);
        return "";
    }

    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        MD5_Update(&md5Context, buffer, file.gcount());
    }
    MD5_Update(&md5Context, buffer, file.gcount());

    unsigned char hash[MD5_DIGEST_LENGTH];

    std::stringstream strstream;
    for (int index = 0; index < MD5_DIGEST_LENGTH; index++) {
        strstream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[index];
    }

    return strstream.str();
}