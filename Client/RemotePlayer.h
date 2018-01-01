//
// Created by yair on 08/12/17.
//

#ifndef ROOT_REMOTEPLAYER_H
#define ROOT_REMOTEPLAYER_H


#include "Player.h"

class RemotePlayer: public Player {
public:
    /**
     * constructor
     */
    RemotePlayer();
    /**
     * constructor
     * @param x
     */
    RemotePlayer(char x);
    /**
     * playing the turn of the client
     * @param coord
     * @param v
     * @param b
     * @param gl
     * @param current
     * @param other
     * @param client
     * @param firstMove
     */
    void playTurn(Shortcuts::coordinate & coord, Shortcuts::coordVec &v,
                  Board &b, GameLogic &gl, char &current, char &other, Client &client, bool &firstMove, Shortcuts::PlayMessage &p);
};


#endif //ROOT_REMOTEPLAYER_H
