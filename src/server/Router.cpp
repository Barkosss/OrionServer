//
// Created by Andrey Baryshev on 04.05.2026.
//
#include "Router.h"
#include<string>
#include <utility>

void Router::addRoute(const std::string& path, HandlerFunction handler) {
    routes[path] = std::move(handler);
}

HandlerFunction Router::getHandler(const std::string& path) const {
    auto it = routes.find(path);
    if (it != routes.end()) {
        return it->second;
    }
    return nullptr;
}