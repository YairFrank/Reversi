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
     * @param port port number
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
    int port;
    int serverSocket;
    /**
     * handling the client
     * @param clientSocket clients socket
     * @return void pointer
     */
    static void* handleClient(void* clientSocket);


    /**
     * connect clients to server
     * @return void pointer
     */
    static void* getClients(void *);

    pthread_t clientConnectingThread;


};

#endif //ROOT_SERVER_H
