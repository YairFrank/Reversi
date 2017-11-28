 /* GameLogic.h
 *
* leah orlin 313357725
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "Shortcuts.h"
#include <vector>
#include <iostream>
using namespace std;

//typedef vector<vector<char> > matrix;
//typedef struct coordinate {int x; int y;} coordinate;

class GameLogic {

public:

	/**
	 * default constructor.
	 */
	GameLogic();


	/**
	 * virtual destructor.
	 */
	virtual ~GameLogic();

	/**
	 * get all player's valid moves.
	 * @param sign player's sign.
	 * @param v vector to hold players possible moves.
	 * @param board game board.
	 */
	void getValidMoves(char sign, vector<Shortcuts::coordinate> &v, Shortcuts::matrix &board);

	/**
	 * check if player has valid moves available.
	 * @param sign player's sign.
	 * @param v vector to hold players possible moves.
	 * @param board game board.
	 * @return true if player has valid moves, false otherwise.
	 */
	bool hasValidMoves(char sign, vector<Shortcuts::coordinate> &v, Shortcuts::matrix &board);

	/**
	 * get a list of player's pieces on the board.
	 * @param s player's sign.
	 * @param board game board.
	 * @return vector of coordinates occupied by specified player on the board.
	 */
	Shortcuts::coordVec getPlayersCoords(char s, Shortcuts::matrix &board) const;

	/**
	 * @return vector of coordinates used to probe the board in all directions.
	 */
	Shortcuts::coordVec getDirections() const;

	/**
	 * swith all the opponents tokens in intervals, after player made his move.
	 * @param s player's sign.
	 * @param x x coordinate of players new move.
	 * @param y y coordinate of players new move.
	 * @param board game board.
	 * @return vector of coordinates of tokens to flip.
	 */
	Shortcuts::coordVec flipTokens(char s, int x, int y,Shortcuts::matrix &board);

	/**
	 * used to check if a vector containing coordinates (a self defined struct) contains certain element.
	 * @param v vector of coordinates.
	 * @param c particular coordinate.
	 * @return true if vector contains coordinate, false otherwise.
	 */
	bool checkForDuplicates(Shortcuts::coordVec &v, Shortcuts::coordinate c);


};

#endif /* GAMELOGIC_H_ */
