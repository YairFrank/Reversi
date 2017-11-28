/*
 * HumanPlayer.h
 *
 *  Created on: Nov 28, 2017
 *      Author: leah
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"
#include "Shortcuts.h"

class HumanPlayer: public Player {
public:
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
	virtual ~HumanPlayer();
};

#endif /* HUMANPLAYER_H_ */



