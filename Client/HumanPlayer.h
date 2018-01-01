// leah orlin 313357725
// yair frank 203699566

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
    void playTurn
            (Shortcuts::coordinate &c, Shortcuts::coordVec &v,
             Board &b, GameLogic &gl, char &current, char &other, Client &cl, bool &firstMove, Shortcuts::PlayMessage &p);
    ~HumanPlayer();
};
#endif //REVERSI_HUMANPLAYER_H
