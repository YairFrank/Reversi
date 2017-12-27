//
// Created by leah on 25/12/17.
//

#include "Command.h"
#include "CloseCommand.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

CloseCommand::CloseCommand() {}

void CloseCommand::execute(clientData *cd, int sid) {
    //get reference to list of games.
    GamesList* games = GamesList::getGamesList();
    int opponentSocket = games->getOpponent(sid);
    int x = -2,y = -2,inidicator,n;
    inidicator = games->removeGame(cd->name);
    if (inidicator == 0) {
        //no such game existed, send message to player who sent the request
        n = write(sid, &inidicator, sizeof(inidicator));
        if (n == -1) {
            cout << "error writing to socket"<< endl;
            return;
        }
    } else {
        //game existed and was deleted, notify both players, by sending them both notification,
        //the player who sent the request-gets simply 1-command executed
        inidicator = 1;
        n = write(sid, &inidicator, sizeof(inidicator));
        if (n == -1) {
            cout << "error writing to socket"<< endl;
            return;
        }
        //opponent gets the move -2,-2 which he will read as "game over"
        coordinate move{x,y};
        n = write(opponentSocket, &move, sizeof(move));
        if (n == -1) {
            cout << "error writing to socket"<< endl;
            return;
        }
    }


}


