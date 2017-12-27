//
// Created by yair on 09/12/17.
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;
#define MAX_CONNECTED_CLIENTS 2



Server::Server(int port): port(port), serverSocket(0) {
    cout << "Server" << endl;

}

void Server::start() {
    bool firstMove = true;
    coordinate move;
    int num;
    int numclients=0;
    //create socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw runtime_error ("Error on binding");
    }

    //start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);

    //define the client socket's structures
    struct sockaddr_in player1Address;
    socklen_t player1AddressLen;

    //define the client socket's structures
    struct sockaddr_in player2Address;
    socklen_t player2AddressLen;

    while (true) {
        cout << "Waiting for client connections..." << endl;

        //accept a players connection
        int player1Socket = accept(serverSocket, (struct sockaddr *)&player1Address, &player1AddressLen);
        cout << "Player 1 connected" << endl;
        numclients++;
        if (player1Socket == -1) {
            throw "Error on accept";
        }

        if (numclients == 1) {
            int op = 3;
            //let player know he is connected and waiting for second player to connect.
            int n = write(player1Socket, &op, sizeof(op));
            if (n == -1) {
                cout << "error writing to socket"<< endl;
                return;
            }
        }

        //accept a new players connection
        int player2Socket = accept(serverSocket, (struct sockaddr *)&player2Address, &player2AddressLen);
        cout << "Player 2 connected" << endl;
        if (player2Socket == -1) {
            throw "Error on accept";
        }
        numclients++;
        if (numclients==2){

            Server::assignSymbol(player1Socket, 1);
            Server::assignSymbol(player2Socket, 2);


            do {
                move = handleClient(player1Socket, move, firstMove);
                move = handleClient(player2Socket, move, firstMove);
                if (isWin(move)) {
                    break;
                }
            } while((move.x != 0) && (move.y != 0));

            //close communication with the client
            close(player1Socket);
            close(player2Socket);
            numclients=0;
        }
    }
}

void Server::stop() {
    close(serverSocket);
}

coordinate Server::handleClient(int clientSocket, coordinate oppMove, bool &firstMove) {
    int n;
    coordinate move;
    coordinate er;
    er.x = 0;
    er.y = 0;
    while (true) {
        //write opponent move to client, if not first move
        if (!firstMove) {
            n = write(clientSocket, &oppMove, sizeof(oppMove));
            if (n == -1) {
                cout << "error writing to socket"<< endl;
                return er;
            }
        }

        //get the players move.
        //either client will give valid coordinate, or -1,-1 if he has no moves
        //or -2,-2 to signal game over.

        n = read(clientSocket, &move, sizeof(move));
        if (firstMove) {
            firstMove = false;
        }
        if (n == -1) {
            cout << "Error reading x" << endl;
            return er;
        }
        if (n == 0) {
            cout << "client disconnected" << endl;
            return er;
        }
        return move;

    }
}

void Server::assignSymbol(int clientSocket, int numPlayer) {
    int n = write(clientSocket, &numPlayer, sizeof(numPlayer));
    if (n == -1) {
        cout << "error writing to socket"<< endl;
        return;
    }
}

bool Server::isWin(coordinate m) {
    if ((m.x == -3) && (m.y == -3)) {
        return true;
    }
    return false;
}