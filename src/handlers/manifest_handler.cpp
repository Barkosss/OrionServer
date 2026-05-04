//
// Created by Andrey Baryshev on 04.05.2026.
//
#include "manifest_handler.h"
#include<nlohmann/json.hpp>
#include "../config/Config.h"
#include "../utils/logger/Logger.h"
#include<vector>

namespace fs = std::filesystem;

nlohmann::json getFiles();

void handleManifest(const HttpRequest& req, HttpResponse& res) {
    try {
        Config::reload();
        nlohmann::json jsonFiles = getFiles();

        res.body() = jsonFiles.dump();
        res.set(http::field::content_type, "application/json");
        res.result(http::status::ok);
    } catch (std::exception& ex) {
        Logger::error("Failed to send response: ", ex.what());
    }
}

nlohmann::json getFiles() {
    try {
        std::string modDir = Config::getInstance().getModsDir();
        auto iterFiles = fs::directory_iterator(modDir);

        std::vector<std::string> files;
        std::string path;
        for (const auto& entry : iterFiles) {
            try {                
                std::filesystem::path absolutePath = entry.path();
                Logger::debug("Get absolute path: ", absolutePath);
                std::filesystem::path basePath = modDir;
                std::filesystem::path relativePath = std::filesystem::relative(absolutePath, basePath);

                path = relativePath.string();                
                Logger::debug("Get relative path: ", path);
            } catch (std::exception& ex) {
                Logger::error("Failed to get relative path: ", ex.what());
                continue;
            }

            if (Config::getInstance().shouldSendToClient(path)) {
                files.push_back(path);
            }
        }

        nlohmann::json json{
            {"files", files},
        };

        return json;
    } catch (std::exception& ex) {
        Logger::error("Failed to get files: ", ex.what());
        return nlohmann::json{
            {"files", {}},
        };
    }
}