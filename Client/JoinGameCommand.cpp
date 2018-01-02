//
// Created by yair on 02/01/18.
//

#include <unistd.h>
#include "JoinGameCommand.h"
#include "RemotePlayer.h"


void JoinGameCommand::execute(char char_array [], int sid) {
    n=write(sid, &char_array , sizeof(char_array));
    if (n == -1)
        throw runtime_error ("server is closed, dude");
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
    Shortcuts::PlayMessage play;
    char winner;
    //if exits while loop - neither players have moves. Game over.
    while (b.hasFreeSpaces()&&play.x!=-2)
        p->playTurn(c, pv, b, gl, current, other, cl, firstMove, play);
    // neither player has valid moves available. Game over.
    //announce winner
    winner = getWinner(current, other);
    if (winner == 't') {
        cout << "Game Over. You tied :-)" << endl;
    } else {
        cout << "Game Over. Winner is " << winner << " :)" << endl;
    }
    //message.str1="close";
    //n=write(cl.getSocket(), &message, 100);
    if (n == -1)
        throw runtime_error ("server is closed, dude");
    delete p;
}

char getWinner(char current, char other) const {
    return b.getMaxPoints(current, other);
}

JoinGameCommand::JoinGameCommand() {}