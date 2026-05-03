//
// Created by Andrey Baryshev on 03.05.2026.
//

#include "Server.h"
#include <boost/asio.hpp>
#include "Router.h"
#include "../session/Session.h"
#include "../utils/logger/Logger.h"

using tcp = boost::asio::ip::tcp;

Server::Server(Router router, unsigned short port) : router(router), port(port) {}

Server::~Server() {

}

void Server::run() {
    try {
        boost::asio::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {boost::asio::ip::address_v4(), port}};
        Logger::info(std::string("Server is running at port:") + std::to_string(port));

        while (true) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            Logger::info(std::string("Accepted connection from ") + socket.remote_endpoint().address().to_string());
            auto session = std::make_shared<Session>(std::move(socket));
            session->start();

            Logger::info("Accepted connection from {}", socket.remote_endpoint().address().to_string());
            std::make_shared<Session>(std::move(socket))->start();
        }

    } catch (const std::exception &ex) {
        Logger::error("Error occurred: {}", ex.what());
    }
}