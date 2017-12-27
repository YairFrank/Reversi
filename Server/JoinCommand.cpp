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

JoinCommand::JoinCommand() {}

void JoinCommand::execute(clientData *cd, int sid) {
    GamesList* games = GamesList::getGamesList();
    int numPlayer;
    int player1socket;

    int opponentSocket = games->getOpponent(sid);

    if (opponentSocket !=0) {
        numPlayer = 2;
        //player was joined to existing game. Notify both players that they can start playing

        //notifying 2nd player (recently joined)
        int n = write(sid, &numPlayer, sizeof(numPlayer));
        if (n == -1) {
            cout << "error writing to socket"<< endl;
            return;
        }

        //notify first player (previously joined)
        numPlayer = 1;
        n = write(opponentSocket, &numPlayer, sizeof(numPlayer));
        if (n == -1) {
            cout << "error writing to socket"<< endl;
            return;
        }
    }

    //No such game is available to join, write message to player - he gets 0, meaning join command failed.
    int n = write(sid, &opponentSocket, sizeof(opponentSocket));
    if (n == -1) {
        cout << "error writing to socket"<< endl;
        return;
    }


}

