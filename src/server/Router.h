//
// Created by Andrey Baryshev on 03.05.2026.
//
#pragma once

#include<map>
#include<string>
#include <functional>
#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;

using HttpRequest = http::request<http::string_body>;
using HttpResponse = http::response<http::string_body>;
using HandlerFunction = std::function<void(const HttpRequest&, HttpResponse&)>;

class Router {
    std::map<std::string, HandlerFunction> routes;

public:
    void addRoute(const std::string &path, HandlerFunction handler);
    HandlerFunction getHandler(const std::string &path) const;
};