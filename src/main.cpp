//
// Created by Andrey Baryshev on 03.05.2026.
//

#include<iostream>
#include <exception>

#include "server/Router.h"
#include "server/Server.h"
#include "./handlers/manifest_handler.h"
#include "./handlers/health_handler.h"
#include "./handlers/file_handler.h"
#include "./handlers/ping_handler.h"
#include "./handlers/sync_handler.h"

int main() {

    try {
        Router router;

        router.addRoute(http::verb::get, "/manifest", handleManifest);
        router.addRoute(http::verb::get, "/file", handleFile);
        router.addRoute(http::verb::get, "/health", handleHealth);
        router.addRoute(http::verb::get, "/ping", handlePing);
        router.addRoute(http::verb::get, "/sync", handleSync);

        Server server(router, 8080);
        server.run();

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
