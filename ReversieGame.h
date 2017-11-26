/*
 * ReversieGame.h
 *
* leah orlin 313357725
 */

#ifndef REVERSIEGAME_H_
#define REVERSIEGAME_H_
#include "Player.h"
#include "Board.h"
#include "GameLogic.h"
#include "Shortcuts.h"

class ReversieGame {
public:

	/**
	 * default constructor.
	 */
	ReversieGame();

	/**
	 * default destructor.
	 */
	virtual ~ReversieGame();

	/**
	 * play the game.
	 */
	void play();

	/**
	 * @return the sign of the winner (t if tied).
	 */
	char getWinner() const;

	/**
	 * check if given coordinate is one of the available moves.
	 * @param c given coordinate.
	 * @param v vector of available moves (coordinates).
	 * @return true if move is valid, false otherwise.
	 */
	bool checkValidInput(Shortcuts::coordinate &c, vector<Shortcuts::coordinate> &v) const;

private:

	bool gameOver;

	Player p1, p2;

	Board b;

	GameLogic gl;






};

#endif /* REVERSIEGAME_H_ */
