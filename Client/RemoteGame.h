//
// Created by yair on 08/12/17.
//

#ifndef ROOT_REMOTEGAME_H
#define ROOT_REMOTEGAME_H


#include "GameLogic.h"
#include "Board.h"
#include "Game.h"

class RemoteGame : public Game {
public:
    /**
	 * default constructor.
	 */
    RemoteGame();

    /**
     * play the game.
     */
    void play();

    /**
     * @return the sign of the winner (t if tied).
     */
    char getWinner(char current, char other) const;

    /**
     * check if given coordinate is one of the available moves.
     * @param c given coordinate.
     * @param v vector of available moves (coordinates).
     * @return true if move is valid, false otherwise.
     */

private:

    Board b;

    GameLogic gl;
};


#endif //ROOT_REMOTEGAME_H
