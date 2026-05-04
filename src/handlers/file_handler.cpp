//
// Created by Andrey Baryshev on 04.05.2026.
//
#include "manifest_handler.h"
#include<nlohmann/json.hpp>
#include<vector>
#include "../utils/logger/Logger.h"

void getFileList(nlohmann::json reqFiles, std::vector<std::string> *files);

void handleFile(const HttpRequest& req, HttpResponse& res) {
    try {
        nlohmann::json reqFiles(req.body());
        std::vector<std::string> files;
        getFileList(reqFiles, files);

        // ...

    } catch (std::exception& ex) {
        Logger::error("Failed to send response: ", ex.what());
    }
}

void getFileList(nlohmann::json reqFiles, std::vector<std::string> *files) {
    // TODO: Get list of file for send
}

