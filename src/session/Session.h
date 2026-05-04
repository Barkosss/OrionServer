//
// Created by Barkosss on 03.05.2026.
//
#pragma once

#ifndef SESSION_H
#define SESSION_H

class Session {
    boost::asio::ip::tcp::socket socket;

public:
    Session(boost::asio::ip::tcp::socket socket) : socket(std::move(socket)) {}

    void start();
};

#endif // SESSION_H