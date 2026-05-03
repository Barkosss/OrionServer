//
// Created by Andrey Baryshev on 03.05.2026.
//

#ifndef MSLAUNCHER_SERVER_H
#define MSLAUNCHER_SERVER_H


class Server {
    unsigned short port;

public:
    Server(unsigned short port);
    ~Server();
    void run();
};


#endif //MSLAUNCHER_SERVER_H