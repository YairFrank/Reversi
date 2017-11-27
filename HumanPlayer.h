/*
 * Player.h
 *
* leah orlin 313357725
 */

#ifndef PLAYER_H_
#define PLAYER_H_
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
	void playTurn(Shortcuts::coordinate &c, Shortcuts::coordVec v, Board &b) override;

private:
	char sign;
	bool hasMoves;
};

#endif /* PLAYER_H_ */



