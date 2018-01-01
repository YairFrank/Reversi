// leah orlin 313357725
// yair frank 203699566

#ifndef AIPLAYER_H
#define AIPLAYER_H


#include "Player.h"

class AIPlayer: public Player {

public:
    AIPlayer();
    AIPlayer(char x);

    /**
     * play a turn with AI logic
     * @param c the coordinate the computer will decide on.
     * @param v vector of all AI's possible moves.
     */
    void playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec &v,
				  Board &b, GameLogic &gamel, char &current, char &other, Client &cl, bool &firstMove, Shortcuts::PlayMessage &p);
	/**
	 *
	 * @param b board.
	 * @return the opponents best score for any possible move, given board at certain position.
	 */
	int getOpponentsBestOption(Board b);

	/**
	 * @return sign of opposite player.
	 */
	char getOppSign() const;

};


#endif //REVERSI_AIPLAYER_H
