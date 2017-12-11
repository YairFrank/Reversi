//
// Created by yair on 05/12/17.
//

#ifndef ROOT_CLIENT_H
#define ROOT_CLIENT_H


#include "Shortcuts.h"

class Client {
public:
    Client ();
    Client (const char *serverIP, int serverPort);
    void connectToServer();
    void sendCoord(Shortcuts::coordinate &c);
    void getCoord(Shortcuts::coordinate &c);
    int getSocket();
private:

    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //ROOT_CLIENT_H
