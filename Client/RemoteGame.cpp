//
// Created by yair on 08/12/17.
//

#include <unistd.h>
#include "RemoteGame.h"
#include "RemotePlayer.h"

using namespace std;

RemoteGame::RemoteGame() : b(Board()), gl(GameLogic()) {
}
void RemoteGame::initialize() {

}
void RemoteGame::play() {
    int num=5, numplay;
    char current, other;
    bool firstMove=true;
    RemotePlayer* p;
    Client cl("127.0.0.1", 8234);
    try {
        cl.connectToServer();
    }
    catch (const char *msg) {
        cout << "Failed to connect to server. Reason:" << msg << endl;
    }
    //writing random
    int n=write(cl.getSocket(), &num, sizeof(num));
    if (n == -1)
        throw "Error writing number from socket";
    n=read(cl.getSocket(), &num, sizeof(num));
    if (n == -1)
        throw runtime_error ("Error reading number from socket");
    numplay=num;
    if (num==2){
        n=write(cl.getSocket(), &num, sizeof(num));
        if (n == -1)
            throw "Error writing number from socket";
    }
    if (numplay==1){
        p = new RemotePlayer('X');
        current='X';
        other='O';
        cout<<"You are X"<<endl;
    }
    if (numplay==2) {
        p = new RemotePlayer('O');
        current='O';
        other='X';
        cout<<"You are O"<<endl;
    }
    Shortcuts::matrix board;
    Shortcuts::coordVec pv;
    Shortcuts::coordinate c;
    char winner;
    //if exits while loop - neither players have moves. Game over.
    while (b.hasFreeSpaces()&&c.x!=-2)
        p->playTurn(c, pv, b, gl, current, other, cl, firstMove);
    // neither player has valid moves available. Game over.
    //announce winner
    winner = RemoteGame::getWinner(current, other);
    if (winner == 't') {
        cout << "Game Over. You tied :-)" << endl;
    } else {
        cout << "Game Over. Winner is " << winner << " :)" << endl;
    }
    try{
        c.x=-3;
        c.y=-3;
        cl.sendCoord(c);
    }catch (const char *msg) {
        cout << "Failed to send coordinates to server. Reason: " << msg << endl;
    }
    delete p;
}

char RemoteGame::getWinner(char current, char other) const {
    return b.getMaxPoints(current, other);
}