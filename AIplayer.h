/*
 * AIplayer.h
 *
 *  Created on: Nov 27, 2017
 *      Author: leah
 */

#ifndef AIPLAYER_H_
#define AIPLAYER_H_

#include "Player.h"
#include "Board.h"
#include "GameLogic.h"

class AIplayer: public Player {
public:
	AIplayer();
	AIplayer(char sigh);
	AIplayer(Board b);
	virtual ~AIplayer();

	/**
	 * holds the logic for AI player move.
	 * @param coord the coordinate will hold the best move for AI.
	 */
	void playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec v);

	/**
	 *
	 * @param b board.
	 * @return the opponents best score for any possible move, given board at certain position.
	 */
	int getOpponentsBestOption(Board b);
	char getOppSign() const;

private:
	Board board;
	GameLogic gl;


};

#endif /* AIPLAYER_H_ */
