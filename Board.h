/*
 * leah orlin 313357725
 */


#ifndef BOARD_H_
#define BOARD_H_
#include "Displayer.h"
#include "ConsoleDisplayer.h"
#include "GameLogic.h"
#include "Shortcuts.h"
#include <vector>
#include <iostream>
using namespace std;


class Board {
public:

	/**
	 * default constructor
	 */
	Board();

	/**
	 * copy constructr
	 * @param b board to be copied
	 */
	Board(const Board &b);

	/**
	 * constructor with parameters for board size and displayer.
	 * @param size board size.
	 * @param d displayer.
	 */
	Board(int size);

	/**
	 * constructor given matrix and displayer.
	 * @param b matrix (2d vector) board.
	 * @param d displayer.
	 */
	Board(Shortcuts::matrix b, ConsoleDisplayer d);

	/**
	 * print the board to screen.
	 */
	void print() const;

	/**
	 * enter a players move on the board.
	 * @param x player's sign.
	 * @param i row.
	 * @param j column.
	 */
	void enterMove(char x, int i, int j);

	/**
	 * @return true if the board has free spaces, false otherwise.
	 */
	bool hasFreeSpaces() const;

	/**
	 * @return the board matrix.
	 */
	Shortcuts::matrix getBoard() const;

	/**
	 * find the winner -who's sign occupies most of the board.
	 * @param a player 1.
	 * @param b player 2.
	 * @return the sign of the winner.
	 */
	char getMaxPoints(char a, char b) const;

	/**
	 * @return the boards displayer.
	 */
	const ConsoleDisplayer& getDisplayer() const;

	/**
	 * @param a first players sign.
	 * @param b second players sign.
	 * @return first players score (his points minus opponents points).
	 */
	int getScore(char a, char b) const;

private:
	Shortcuts::matrix board;
	ConsoleDisplayer displayer;
};

#endif /* BOARD_H_ */
