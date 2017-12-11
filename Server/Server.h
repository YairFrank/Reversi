//
// Created by yair on 09/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


typedef struct coordinate {int x; int y;} coordinate;

class Server {
public:

    Server(int port);
    void start();
    void stop();

private:
    int port;
    int serverSocket;

    coordinate handleClient(int clientSocket, coordinate move, bool &firstMove);
    void assignSymbol(int clientSocket, int numPlayer);
    bool isWin(coordinate m);
};

#endif //SERVER_SERVER_H
