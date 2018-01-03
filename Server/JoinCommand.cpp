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



JoinCommand::JoinCommand(){}

void JoinCommand::execute(vector <string> cd, int sid) {
    cout<<"enters joincommand"<<endl;
    GamesList* games = GamesList::getGamesList();
    int numPlayer;
    int opponentSocket;
    //gameData gd;
    opponentSocket = games->getOpponent(cd[0]);


    if (opponentSocket !=0) {

        JoinCommand::runGame(cd[0],opponentSocket,sid);


    }

    //No such game is available to join, write message to player - he gets 0, meaning join command failed.
    int n = write(sid, &opponentSocket, sizeof(opponentSocket));
    if (n == -1) {
        cout << "error writing to socket"<< endl;
        return;
    }
}

void JoinCommand::runGame(string name, int player1Socket, int player2Socket) {
    GamesList* games = GamesList::getGamesList();

    int n;
    coordinate move;
    coordinate er;
    er.x = 0;
    er.y = 0;
    bool firstMove = true;
    int num=1;
    cout<<"joined"<<endl;

    JoinCommand::assignSymbol(player1Socket, 1);
    JoinCommand::assignSymbol(player2Socket, 2);



    do {
        move = JoinCommand::passMove(player1Socket, move, firstMove);
        move = JoinCommand::passMove(player2Socket, move, firstMove);
        if (JoinCommand::isWin(move)) {
            break;
        }
    } while((move.x != 0) && (move.y != 0));

    //close communication with the client
    games->removeGame(name);
    close(player1Socket);
    close(player2Socket);

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



