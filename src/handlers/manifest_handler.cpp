//
// Created by Andrey Baryshev on 04.05.2026.
//
#include "manifest_handler.h"
//#include<nlohman/json.hpp>

void handleManifest(const HttpRequest&, const HttpResponse&) {
    nlohmann::json json;
    json["files"] = {
        {"mods/example.jar", "hash12345"},
        {"config/options.txt", "hash67890"}
    };

    res.body() = json.dump();
    res.set(http::field::content_type, "application/json");
    res.result(http::status::ok);
}