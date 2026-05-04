//
// Created by Andrey Baryshev on 04.05.2026.
//
#include "manifest_handler.h"
#include<nlohmann/json.hpp>
#include "../utils/logger/Logger.h"

void handleHealth(const HttpRequest& req, HttpResponse& res) {
    try {
        res.result(http::status::ok);
    } catch (std::exception& ex) {
        Logger::error("Failed to send response: {}", ex.what());
    }
}