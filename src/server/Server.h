//
// Created by Andrey Baryshev on 03.05.2026.
//

#ifndef MSLAUNCHER_SERVER_H
#define MSLAUNCHER_SERVER_H

#include "Router.h"

class Server {
    Router router;
    unsigned short port;

public:
    Server(Router router, unsigned short port);
    ~Server();
    void run();
};


#endif //MSLAUNCHER_SERVER_H