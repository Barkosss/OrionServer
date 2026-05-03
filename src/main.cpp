//
// Created by Andrey Baryshev on 03.05.2026.
//

#include<iostream>
#include <exception>

#include "server/Router.h"
#include "server/Server.h"

int main() {

    try {
        Router router;

        router.addRoute("/manifest", nullptr);
        router.addRoute("/file", nullptr);
        router.addRoute("filelist", nullptr);
        router.addRoute("health", nullptr);

        Server server(router, 8080);
        server.run();

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
