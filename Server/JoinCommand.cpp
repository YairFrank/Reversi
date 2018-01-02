//
// Created by leah on 25/12/17.
//

#include "Command.h"
#include "JoinCommand.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <cstdlib>

typedef struct gameData{string name;int player1Socket; int player2socket; JoinCommand* myClass;} gameData;

JoinCommand::JoinCommand(){}

void JoinCommand::execute(vector <string> cd, int sid) {
    GamesList* games = GamesList::getGamesList();
    int numPlayer;
    int opponentSocket;
    gameData gd;
    opponentSocket = games->getOpponent(sid);


    if (opponentSocket !=0) {
        gd.name = cd[0];
        gd.player1Socket = opponentSocket;
        gd.player2socket = sid;
        vector<pthread_t> threads;
        pthread_t thread;
        gameData* gdp= &gd;
        gd.myClass = this;


        threads.push_back(thread);
        int rc = pthread_create(&thread, NULL, runGame, (void*)gdp);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }

    }

    //No such game is available to join, write message to player - he gets 0, meaning join command failed.
    int n = write(sid, &opponentSocket, sizeof(opponentSocket));
    if (n == -1) {
        cout << "error writing to socket"<< endl;
        return;
    }
}

void* JoinCommand::runGame(void *gd) {
    GamesList* games = GamesList::getGamesList();
    int player1Socket;
    int player2Socket;
    string name;
    int n;
    coordinate move;
    coordinate er;
    er.x = 0;
    er.y = 0;
    bool firstMove = true;
    int num=1;
    gameData *data = (gameData*)gd;
    name = data->name;
    player1Socket = data->player1Socket;
    player2Socket = data->player2socket;
    JoinCommand* jc = data->myClass;
    n=write(data->player1Socket, &num, sizeof(num));
    if (n == -1) {
        cout << "error writing to socket"<< endl;
    }
    //jc->assignSymbol(player1Socket, 1);
    //jc->assignSymbol(player2Socket, 2);



    do {
        move = jc->passMove(player1Socket, move, firstMove);
        move = jc->passMove(player2Socket, move, firstMove);
        if (jc->isWin(move)) {
            break;
        }
    } while((move.x != 0) && (move.y != 0));

    //close communication with the client
    games->removeGame(name);
    close(player1Socket);
    close(player2Socket);
    pthread_exit(NULL);

}

coordinate JoinCommand::passMove(int clientSocket, coordinate oppMove, bool &firstMove) {
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

void JoinCommand::assignSymbol(int clientSocket, int numPlayer) const {
    int n = write(clientSocket, &numPlayer, sizeof(numPlayer));
    if (n == -1) {
        cout << "error writing to socket" << endl;
        return;
    }
}

bool JoinCommand::isWin(coordinate m) {
    if ((m.x == -3) && (m.y == -3)) {
        return true;
    }
    return false;
}



