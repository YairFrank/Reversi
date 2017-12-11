//
// Created by yair on 08/12/17.
//

#ifndef ROOT_REMOTEPLAYER_H
#define ROOT_REMOTEPLAYER_H


#include "Player.h"

class RemotePlayer: public Player {
public:
    RemotePlayer();
    RemotePlayer(char x);
    void playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec &v,
                  Board &b, GameLogic &gl, char &current, char &other, Client &client, bool &firstMove);
};


#endif //ROOT_REMOTEPLAYER_H
