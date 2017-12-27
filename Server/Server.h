//
// Created by yair on 09/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include <netinet/in.h>

typedef struct coordinate {int x; int y;} coordinate;


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
    int port;
    static int serverSocket;
    /**
     * handling the client
     * @param clientSocket
     * @param move
     * @param firstMove
     * @return a coordinate to each client
     */
    coordinate handleClient(int clientSocket, coordinate move, bool &firstMove);
    /**
     * assigning a number for each client
     * @param clientSocket
     * @param numPlayer
     */
    void assignSymbol(int clientSocket, int numPlayer);
    /**
     * checking if the game is ended
     * @param m
     * @return
     */
    bool isWin(coordinate m);

    static  void *connect (void* args);
};

#endif //SERVER_SERVER_H
