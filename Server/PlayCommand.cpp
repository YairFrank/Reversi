//
// Created by leah on 25/12/17.
//

#include "PlayCommand.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

PlayCommand::PlayCommand(){}

void PlayCommand::execute(clientData *cd, int sid) {
    GamesList* games = GamesList::getGamesList();
    int n, valid = 1;  //player is registered


    //find players socket in list of games, to find the game that he participates in
    int oppSocket = games->getOpponent(sid);
    if (oppSocket == 0) {
        //the player sending the move does not participate in any game, send him error msg
        n = write(sid, &oppSocket, sizeof(oppSocket));
        if (n == -1) {
            cout << "error writing to socket"<< endl;
            return;
        }
    } else {
        //player participates in game. Notify him that his move was accepted, and notify his opponent of his move
        n = write(sid, &valid, sizeof(valid));
        if (n == -1) {
            cout << "error writing to socket"<< endl;
            return;
        }
        //notify opponent of move
        coordinate move{cd->x,cd->y};
        n = write(oppSocket, &move, sizeof(move));
        if (n == -1) {
            cout << "error writing to socket"<< endl;
            return;
        }

    }

}