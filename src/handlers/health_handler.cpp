//
// Created by Andrey Baryshev on 04.05.2026.
//
#include "manifest_handler.h"
#include<nlohmann/json.hpp>
#include "../utils/logger/Logger.h"

void handleHealth(const HttpRequest& req, HttpResponse& res) {
    try {
        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");

        nlohmann::json response;
        response["status"] = "healthy";
        response["timestamp"] = std::time(nullptr);

        res.body() = response.dump();
        res.prepare_payload();

    } catch (std::exception& ex) {
        Logger::error("Failed to send response: {}", ex.what());
    }
}