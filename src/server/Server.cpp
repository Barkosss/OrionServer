//
// Created by Andrey Baryshev on 03.05.2026.
//

#include<iostream>
#include "Server.h"
#include "../utils/logger/Logger.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>

using boost::asio::ip::tcp;

Server::Server(Router router, unsigned short port) : router(std::move(router)), port(port) {
    Logger::info("Server object created on port {}", port);
}

Server::~Server() {
    Logger::info("Server object destroyed");
}

void Server::run() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));

        Logger::info("Server listening on port {}", port);

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            Logger::info("Client connected from ", socket.remote_endpoint().address().to_string());

            beast::flat_buffer buffer;
            http::request<http::string_body> req;
            beast::error_code ec;

            http::read(socket, buffer, req, ec);

            if (ec) {
                Logger::error("Failed to read request: {}", ec.message());
                continue;
            }        

            std::string path = req.target();
            Logger::info("Request: ", req.method_string());

            auto handler = router.getHandler(req.method(), path);

            http::response<http::string_body> res;

            if (handler) {
                handler(req, res);
            } else { // 404
                res.result(http::status::not_found);
                res.body() = "404 Not Found";
                res.set(http::field::content_type, "text/plain");
            }

            res.set(http::field::content_length, std::to_string(res.body().size()));
            http::write(socket, res, ec);

            if (ec) {
                Logger::error("Failed to send response: {}", ec.message());
            }

            socket.shutdown(tcp::socket::shutdown_send, ec);
        }

    } catch (const std::exception& ex) {
        Logger::error("Server error: ", ex.what());
    }
}