//
// Created by yair on 05/12/17.
//

#ifndef ROOT_CLIENT_H
#define ROOT_CLIENT_H


#include "Shortcuts.h"

class PlayMessage;

class Client {
public:
    /**
     * constructor
     */
    Client ();
    /**
     * constructor
     * @param serverIP
     * @param serverPort
     */
    Client (const char *serverIP, int serverPort);
    /**
     * connecting to the server
     */
    void connectToServer();
    /**
     * writing the coordinate to the server
     * @param c
     */
    void sendMessage(Shortcuts::PlayMessage& play);
    /**
     * reading the coordinate to the server
     * @param c
     */
    void getMessage(Shortcuts::PlayMessage& play);
    /**
     * getting the socket number
     * @return the socket number
     */
    int getSocket();
private:

    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //ROOT_CLIENT_H
