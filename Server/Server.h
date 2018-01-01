//
// Created by leah on 28/12/17.
//

#ifndef ROOT_SERVER_H
#define ROOT_SERVER_H

#include "CommandsManager.h"


class Server {
public:
    /**
     * constructor
     * @param port
     */
    Server(int port);
    /**
     * starting the server
     */
    void start();
    /**
     * stopping the server
     */
    void stop();

private:
    bool  quit;
    int port;
    int serverSocket;
    /**
     * handling the client
     * @param clientSocket
     * @param move
     * @param firstMove
     * @return a coordinate to each client
     */
    static void* handleClient(void* clientSocket);
    /**
     * assigning a number for each client
     * @param clientSocket
     * @param numPlayer
     */
    void assignSymbol(int clientSocket, int numPlayer);

public:
    bool isQuit() const;

    void setQuit(bool quit);

    int getServerSocket() const;

    void setServerSocket(int serverSocket);

    int getPort() const;

    void setPort(int port);

private:
    /**
     * checking if the game is ended
     * @param m
     * @return
     */
    bool isWin(coordinate m);

    static void* quitStatus(void*);


    static void* getClients(void *);

    pthread_t clientConnectingThread;
};

#endif //ROOT_SERVER_H
