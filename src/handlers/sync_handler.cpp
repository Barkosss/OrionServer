//
// Created by Andrey Baryshev on 05.05.2026.
//
#include "sync_handler.h"
#include "nlohmann/json.hpp"
#include "../server/Router.h"
#include "../config/Config.h"
#include "../utils/logger/Logger.h"

nlohmann::json getUpgradeFiles(nlohmann::json files);

void handleSync(const HttpRequest &req, HttpResponse &res) {
    try {
        nlohmann::json userJson(req.body());

        if (!userJson.contains("files") || !userJson["files"].is_string()) {
            res.body() = nlohmann::json({"error", "Required field \"files\" with filename with hash"});
            res.result(http::status::bad_request);
            return;
        }

        nlohmann::json resJson = getUpgradeFiles(userJson["files"]);

        res.body() = resJson;
        res.result(http::status::ok);

    } catch (std::exception& ex) {
        Logger::error("Failed to send response (/sync): {}", ex.what());
    }
}

nlohmann::json getUpgradeFiles(nlohmann::json files) {
    nlohmann::json json{};

    for (const auto& filename : files) {
        Logger::debug("filename: {} | hash: {}", filename, files[filename]);
    }

    return json;
}

std::string getHash(std::string filename) {
    return "";
}