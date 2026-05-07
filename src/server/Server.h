//
// Created by Andrey Baryshev on 03.05.2026.
//

#ifndef MSBackend_SERVER_H
#define MSBackend_SERVER_H

#include "Router.h"

class Server {
    Router router;
    unsigned short port;

public:
    Server(Router router, unsigned short port);
    ~Server();
    void run();
};


#endif //MSBackend_SERVER_H