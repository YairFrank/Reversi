//
// Created by yair on 08/12/17.
//

#include <unistd.h>
#include "RemoteGame.h"
#include "RemotePlayer.h"

using namespace std;

RemoteGame::RemoteGame() : b(Board(4)), gl(GameLogic()) {
}
void RemoteGame::initialize() {

}
void RemoteGame::play() {
    int numplay, waitmsg, n, num;
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

    //get information from server that client should wait for another player to connect/player symbol
    n=read(cl.getSocket(), &waitmsg, sizeof(waitmsg));
    if (n == -1)
        throw runtime_error ("Error reading number from socket");
    if (waitmsg == 3) {
        cout << "waiting for another player to connect..." << endl;
        //get information from server about player's symbol
        n=read(cl.getSocket(), &num, sizeof(num));
        if (n == -1)
            throw runtime_error ("Error reading number from socket");
    }

    //in case current client was not first to connect.
    if (waitmsg != 3)
        numplay = waitmsg;
    else {
        numplay=num;
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
        cout << "Waiting for other player..." << endl;
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