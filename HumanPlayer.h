//
// Created by yair on 28/11/17.
//

#ifndef REVERSI_HUMANPLAYER_H
#define REVERSI_HUMANPLAYER_H

#include "Player.h"


class HumanPlayer: public Player {

public:
    /**
     * default constructor.
     */
    HumanPlayer();

    /**
     * constructor for player, given sign.
     * @param x player's sign.
     */
    HumanPlayer(char x);

    /**
     * player plays a turn.
     * @param c coordinate to place player on.
     */
    void playTurn(Shortcuts::coordinate &c, Shortcuts::coordVec v, Board &b);

private:
    char sign;
    bool hasMoves;
};
#endif //REVERSI_HUMANPLAYER_H
