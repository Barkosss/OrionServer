//
// Created by Andrey Baryshev on 04.05.2026.
//
#include "manifest_handler.h"
#include<nlohmann/json.hpp>
#include<fstream>
#include "../config/Config.h"
#include "../utils/logger/Logger.h"

using std::string;

void handleFile(const HttpRequest& req, HttpResponse& res) {
    Logger::info("Received /file request");

    try {
        auto request = nlohmann::json::parse(req.body());
        
        if (!request.contains("files") || !request["files"].is_array()) {
            Logger::error("Invalid request: missing or invalid 'files' field");
            res.result(http::status::bad_request);
            res.body() = R"({"error": "Missing or invalid 'files' field"})";
            res.set(http::field::content_type, "application/json");
            return;
        }

        auto files = request["files"];

        if (files.empty()) {
            Logger::warning("Empty file list requested");
            res.result(http::status::bad_request);
            res.body() = R"({"error": "Empty file list"})";
            res.set(http::field::content_type, "application/json");
            return;
        }

        Logger::debug("Zip request for {} file(s)", files.size());

        string modsDir = Config::getInstance().getModsDir();
        string zipFilename = "temp_" + std::to_string(time(nullptr)) + ".zip";
        
        string zipCmd;
        #ifdef _WIN32
            zipCmd = "powershell -Command \"Compress-Archive -Path ";
            for (auto& file : files) {
                std::string fullPath = modsDir + "/" + file.get<std::string>();
                zipCmd += "\"" + fullPath + "\",";
                Logger::debug("Zipped filename {}", fullPath);
            }
            zipCmd.pop_back();
            zipCmd += " -DestinationPath " + zipFilename + "\"";
        #else
            zipCmd = "cd " + modsDir + " && zip -j " + zipPath;
            for (auto& file : files) {
                zipCmd += " \"" + file.get<std::string>() + "\"";
            }
        #endif

        Logger::debug("Executing: {}", zipCmd);

        int result = system(zipCmd.c_str());
        if (result != 0) {
            Logger::error("ZIP creation failed with code: {}", result);
            res.result(http::status::internal_server_error);
            res.body() = nlohmann::json::parse({"error", "Failed to create archive"});
            res.set(http::field::content_type, "application/json");
            return;
        }

        if (!std::filesystem::exists(zipFilename)) {
            Logger::error("ZIP file not created: {}", zipFilename);
            res.result(http::status::internal_server_error);
            res.body() = nlohmann::json::parse({"error", "Archive not created"});
            res.set(http::field::content_type, "application/json");
            return;
        }

        std::ifstream zipFile(zipFilename, std::ios::binary);
        if (!zipFile.is_open()) {
            Logger::error("failed to open zip file: {}", zipFilename);
            res.result(http::status::internal_server_error);
            res.body() = nlohmann::json::parse({"error", "Failed to read archive"});
            res.set(http::field::content_type, "application/json");
            return;
        }

        zipFile.seekg(0, std::ios::end);
        size_t zipSize = zipFile.tellg();
        zipFile.seekg(0, std::ios::beg);

        Logger::info("Zip file({}) size: {} bytes", zipFilename, zipSize);

        if (zipSize < 22) {
            Logger::error("ZIP file is too small: {} bytes", zipSize);
            res.result(http::status::internal_server_error);
            res.body() = nlohmann::json::parse({"error", "Invalid archive"});
            res.set(http::field::content_type, "application/json");
            return;
        }

        char signature[4];
        zipFile.read(signature, 4);
        if (signature[0] != 'P' || signature[1] != 'K') {
            Logger::error("Invalid ZIP signature");
            res.result(http::status::internal_server_error);
            res.body() = nlohmann::json::parse({"error", "Invalid archive signature"});
            res.set(http::field::content_type, "application/json");
            return;
        }
        zipFile.seekg(0, std::ios::beg);

        string content((std::istreambuf_iterator<char>(zipFile)), {});
        zipFile.close();

        res.body() = content;
        res.set(http::field::content_type, "application/zip");
        res.set(http::field::content_disposition, "attachment; filename=\"update.zip\"");
        res.set(http::field::content_length, std::to_string(content.size()));
        res.result(http::status::ok);

        Logger::info("ZIP send successfully ({} bytes)", content.size());

        if (std::remove(zipFilename.c_str()) != 0) {
            Logger::warning("Failed to delete temporary file: {}", zipFilename);
        } else {
            Logger::debug("Temporary file deleted: {}", zipFilename);
        }

    } catch (const nlohmann::json::exception& ex) {
        Logger::error("JSON parse error: {}", ex.what());
        res.result(http::status::bad_request);
        res.body() = nlohmann::json::parse({"error", "Internal server error"});
        res.set(http::field::content_type, "application/json");

    } catch (const std::exception& ex) {
        Logger::error("Unexpected error: {}", ex.what());
        res.result(http::status::internal_server_error);
        res.body() = nlohmann::json::parse({"error", "Internal server error"});
        res.set(http::field::content_type, "application/json");
    }
}
