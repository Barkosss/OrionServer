//
// Created by Andrey Baryshev on 04.05.2026.
//
#include "Router.h"
#include<string>
#include<utility>
#include "../utils/logger/Logger.h"

void Router::addRoute(const http::verb method, const std::string& path, HandlerFunction handler) {
    routes[path][method] = handler;
    Logger::info("Route registered: {}{}", method, path);
}

HandlerFunction Router::getHandler(const http::verb method, const std::string& path) const {
    auto itPath = routes.find(path);
    if (itPath == routes.end()) {
        return nullptr;
    }

    const auto& methodMap = itPath->second;
    auto itMethod = methodMap.find(method);
    if (itMethod == methodMap.end()) {
        return nullptr;
    }

    return itMethod->second;
}