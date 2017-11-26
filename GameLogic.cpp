/*
 * GameLogic.cpp
 *
 * leah orlin 313357725
 */

#include "GameLogic.h"
#include <algorithm>
#include <vector>
#include <set>



GameLogic::GameLogic() {

}

GameLogic::~GameLogic() {
}

void GameLogic::getValidMoves(char sign, vector<Shortcuts::coordinate> &v, Shortcuts::matrix &board) {
	int x, y, z = 0,xStart,yStart;
	int outOfBounds = board.size() - 1;
	Shortcuts::coordinate coord,dir, move,temp;
	Shortcuts::coordVec playerPos, directions;
	Shortcuts::coordVec::iterator i,i2,i3;

	//get vector of player positions on the board.
	playerPos = GameLogic::getPlayersCoords(sign, board);
	//get vector of directions by which we will probe spaces around a cell.
	directions = GameLogic::getDirections();
	//for every piece of that player on the board
	for (i = playerPos.begin(); i != playerPos.end(); ++i) {
		coord = *i;
		//original coordinate of player-occiupied slot.
		xStart = coord.x;
		yStart = coord.y;
		x = xStart;
		y = yStart;
		//for every direction around the cell
		for (i2 = directions.begin(); i2 != directions.end(); i2++) {
			dir = *i2;
			x += dir.x;
			y += dir.y;
			//check boundary stipulation
			while ((x >= 0) && (x < outOfBounds) && (y >= 0) && (y < outOfBounds)) {
				//if reached a cell already occupied by himself - not valid. Keep looking.
				if (board[x][y] == sign) {
					//return to original starting location to probe in a new direction.
					x = xStart;
					y = yStart;
					break;
				} else if (board[x][y] == ' '){
					//if reached and empty slot
					if (z == 0) {
						//reached empty square, without passing opponent first.Not a valid move.
						x = xStart;
						y = yStart;
						break;
					} else {
						//reached empty slot after passing opponent-occupied spaces. Potentially valid move.
						move.x = x + 1;
						move.y = y + 1;
						//add the slot, while avoiding duplicates.
						if (!GameLogic::checkForDuplicates(v,move)) {
							v.push_back(move);
						}
						x = xStart;
						y = yStart;
						break;
					}
				} else {
					//reached opponent occupied square
					z++;	//flag
					//continue moving in the same direction.
					x += dir.x;
					y += dir.y;
					continue;
				}
			}
			z = 0;
			x = xStart;
			y = yStart;

		}
	}
}

Shortcuts::coordVec GameLogic::flipTokens(char s, int x, int y, Shortcuts::matrix &board) {
	int outOfBounds = board.size() - 1;
	int xStart, yStart,z = 0;
	Shortcuts::coordVec directions,flips, mayFlip;
	Shortcuts::coordVec::iterator i, i2;
	Shortcuts::coordinate dir, op;

	//pretty much the same logic of getting valid moves, with obvious changes.
	directions = GameLogic::getDirections();
	/*start at the coordinate of newly-positioned piece. probe all directions searching for
	a line of opponent pieces blocked by player's. */
	xStart = x;
	yStart = y;
	for (i = directions.begin(); i != directions.end(); i++) {
				dir = *i;
				x += dir.x;
				y += dir.y;
				//check boundary stipulation
				while ((x >= 0) && (x < outOfBounds) && (y >= 0) && (y < outOfBounds)) {
					if (board[x][y] == ' ') {
						//if reached empty slot, opponent's pieces are not blocked by player's.Realese them.
						mayFlip.clear();
						//return to original starting location to probe in a new direction.
						x = xStart;
						y = yStart;
						break;
					} else if (board[x][y] == s){
						if (z == 0) {
							//reached self-occupied square, without passing opponent first.No tokens to flip.
							//return to original starting location to probe in a new direction.
							x = xStart;
							y = yStart;
							break;
						} else {
							/*passed one opponent at least, now known to be blocked by another
							 * of player's pieces. Add all opponent tokens passed until now to array of
							 * tokens to be flipped.
							 */
							for (unsigned int j = 0; j < mayFlip.size(); j++) {
								flips.push_back(mayFlip[j]);
							}
							//clear array of possible tokens to flip.
							mayFlip.clear();
							x = xStart;
							y = yStart;
							break;
						}
					} else {
						//reached opponent occupied square
						z++;	//flag
						op.x = x;
						op.y = y;
						/*add coordinate to array of tokens which may be flipped, depending
						 * on whether they turn out to be blocked by another of player's pieces.
						 */
						mayFlip.push_back(op);
						x += dir.x;
						y += dir.y;
						continue;
					}
				}
				z = 0;
				x = xStart;
				y = yStart;
			}
	return flips;
	}



bool GameLogic::hasValidMoves(char sign, vector<Shortcuts::coordinate> &v, Shortcuts::matrix &board) {
	GameLogic::getValidMoves(sign,v, board);
	//check if there are no moves available, check syntax
	//if array of valid moves is empty, there are no moves available.
	if (v.size() == 0) {
		return false;
	}
	return true;
}

Shortcuts::coordVec GameLogic::getPlayersCoords(char s, Shortcuts::matrix &board) const {
	vector<Shortcuts::coordinate> vec;
	Shortcuts::coordinate c;
	//scan board and find coordinates occupied by player.
	for (unsigned int i = 0; i < board.size(); i ++) {
		for (unsigned int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == s) {
				c.x = i;
				c.y = j;
				vec.push_back(c);
			}
		}
	}
	return vec;
}

Shortcuts::coordVec GameLogic::getDirections() const {

	/*make an array of directions- values by which x and y will be altered in order to
	 * scan the board around a specific coordinate.
	 */

	Shortcuts::coordinate dir;
	Shortcuts::coordVec directions;
	for (int b = -1; b < 2; b++) {
		for (int c = -1; c < 2; c++) {
			if (!(b == 0 && c== 0)) {
				dir.x = b;
				dir.y = c;
				directions.push_back(dir);
			}
		}
	}
	return directions;

}

bool GameLogic::checkForDuplicates(Shortcuts::coordVec& v,
		Shortcuts::coordinate c) {
	Shortcuts::coordVec::iterator i;
	Shortcuts::coordinate temp;
	for (i = v.begin(); i != v.end(); i++) {
		temp = *i;
		if ((c.x == temp.x) && (c.y == temp.y)) {
			return true;
		}
	}
	return false;
}

