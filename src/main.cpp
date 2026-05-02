//
// Created by Andrey Baryshev on 03.05.2026.
//

#include<iostream>
#include <exception>

#include "server/Server.h"

int main() {

    try {

        Server server(8080);
        server.run();

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
