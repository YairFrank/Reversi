/*
 * Player.h
 *
* leah orlin 313357725
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "Shortcuts.h" //in order to get the typedefs

class Player {

public:

	/**
	 * default constructor.
	 */
	Player();

	/**
	 * constructor for player, given sign.
	 * @param x player's sign.
	 */
	Player(char x);

	/**
	 * return true if player has available moves, false otherwise.
	 */
	bool hasOptions() const;

	/**
	 * player plays a turn.
	 * @param c coordinate to place player on.
	 * @param v vector of possible moves
	 */
	void playTurn(Shortcuts::coordinate &c, Shortcuts::coordVec &v);

	/**
	 * set boolean hasMoves.
	 * @param x boolean to set value to.
	 */
	void setHasMoves(bool x);

	/**
	 * get value of boolean hasMoves.
	 * @return true if player has available moves, false otherwise.
	 */
	bool getHasMoves() const;

	/**
	 * @return vector of coordinates of available moves for player.
	 */
	vector<Shortcuts::coordinate> getMoves() const;

	/**
	 * @return player's sign.
	 */
	char getSign() const;

protected:

	char sign;

	bool hasMoves;

	vector<Shortcuts::coordinate> moves;

};

#endif /* PLAYER_H_ */



