/*
 * ReversieGame.h
 *
* leah orlin 313357725
 */

#ifndef REVERSIEGAME_H_
#define REVERSIEGAME_H_
#include "Board.h"
#include "GameLogic.h"
#include "Shortcuts.h"
#include "AIPlayer.h"
#include "HumanPlayer.h"

class ReversieGame {
public:

	/**
	 * default constructor.
	 */
	ReversieGame(int a);

	/**
	 * play the game.
	 */
	void play();

	/**
	 * @return the sign of the winner (t if tied).
	 */
	char getWinner(Player* p1, Player* p2) const;

	/**
	 * check if given coordinate is one of the available moves.
	 * @param c given coordinate.
	 * @param v vector of available moves (coordinates).
	 * @return true if move is valid, false otherwise.
	 */
	bool checkValidInput(Shortcuts::coordinate &c, vector<Shortcuts::coordinate> &v) const;

private:

	bool gameOver;

	Board b;

	GameLogic gl;

	int gameOption;

    int a;



};

#endif /* REVERSIEGAME_H_ */
