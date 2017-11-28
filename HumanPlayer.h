/*
 * Player.h
 *
* leah orlin 313357725
 */

#ifndef REVERSI_HUMANPLAYER_H
#define REVERSI_HUMANPLAYER_H
#include "Shortcuts.h" //in order to get the typedefs
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
    void playTurn(Shortcuts::coordinate &c);

private:
    char sign;
    bool hasMoves;
};




#endif //REVERSI_HUMANPLAYER_H
