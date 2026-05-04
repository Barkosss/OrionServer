//
// Created by Andrey Baryshev on 03.05.2026.
//

#include "Server.h"
#include "../utils/logger/Logger.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

Server::Server(Router router, unsigned short port) : port(port) {
    this->router = router;
    this->port = port;
    Logger::info("Server object created on port ", port);
}

Server::~Server() {
    Logger::info("Server object destroyed");
}

void Server::run() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));

        Logger::info("Server listening on port ", port);

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            Logger::info("Client connected from ", socket.remote_endpoint().address().to_string());

            std::string message = "Hello from MSLauncher!\n";
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }

    } catch (const std::exception& ex) {
        Logger::error("Server error: ", ex.what());
    }
}