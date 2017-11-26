/*
 * ReversieGame.cpp
 *
 *  Created on: Nov 11, 2017
* leah orlin 313357725
 */

#include "Shortcuts.h"
#include "ReversieGame.h"
using namespace std;
//typedef vector<vector<char> > matrix;
//typedef struct coordinate {int x; int y;} coordinate;

ReversieGame::ReversieGame() :
		gameOver(false), p1(Player('X')), p2(Player('O')), b(Board()), gl(
				GameLogic(/*b.getBoard()*/)) {
}

ReversieGame::~ReversieGame() {
	// TODO Auto-generated destructor stub
}

void ReversieGame::play() {
	Shortcuts::matrix board;
	Player current = p1;
	Shortcuts::coordVec p1v;
	Shortcuts::coordVec p2v;
	Shortcuts::coordVec v, flips;
	Shortcuts::coordVec::iterator it;
	Shortcuts::coordinate c, f;
	char winner;
	//if exits while loop - neither players have moves. Game over.
	board = b.getBoard();
	while (b.hasFreeSpaces()
			&& (gl.hasValidMoves(p1.getSign(), p1v, board)
					|| gl.hasValidMoves(p2.getSign(), p2v, board))) {

		if (p2v.size() == 0) {
			gl.hasValidMoves(p2.getSign(), p2v, board);
		}
		if (p1v.size() != 0) {
			p1.setHasMoves(true);

		}
		if (p1v.size() == 0){
			cout<< "no moves left for X" <<endl;
			p1.setHasMoves(false);
		}
		if (p2v.size() != 0) {
			p2.setHasMoves(true);
		}
		if (p2v.size() == 0)
		{
			cout<< "no moves left for O" <<endl;
			p2.setHasMoves(false);
		}

			b.print();
			cout << current.getSign() << ": It's your move." << endl;
			if (current.getHasMoves()) {
				if (current.getSign() == p1.getSign()) {
					v = p1v;
				} else {
					v = p2v;
				}
				cout << "vector size: " << v.size()<<endl;
				for (unsigned int i = 0; i < v.size(); i++) {

					cout << '(' << v[i].x << ',' << v[i].y << ") ";
				}
				cout << endl;
				current.playTurn(c);

				//make sure valid move was entered.
				while (!ReversieGame::checkValidInput(c, v)) {
					cout << "please enter valid move" << endl;
					current.playTurn(c);
				}

				//alter board
				b.enterMove(current.getSign(), c.x, c.y);
				flips = gl.flipTokens(current.getSign(), c.x - 1, c.y - 1,
						board);
				for (it = flips.begin(); it != flips.end(); it++) {
					f = *it;
					b.enterMove(current.getSign(), f.x + 1, f.y + 1);
				}

				//print board after update
				b.print();
				cout << current.getSign() << " played (" << c.x << ',' << c.y
						<< ')' << endl;
				p1v.clear();
				p2v.clear();
				board = b.getBoard();
			} else {
			//player had no moves available
			cout << "No possible moves. Play passes back to the other player"
					<< endl;
		}
		//switch player
		if (current.getSign() == p1.getSign()) {
			current = p2;
		} else {
			current = p1;
		}

	}
	// neither player has valid moves available. Game over.
	//announce winner

	winner = ReversieGame::getWinner();
	if (winner == 'c') {
		cout << "Game Over. You tied :-)" << endl;
	} else {
		cout << "Game Over. Winner is " << winner << " :)" << endl;
	}
}

char ReversieGame::getWinner() const {
	return b.getMaxPoints(p1.getSign(), p2.getSign());
}

bool ReversieGame::checkValidInput(Shortcuts::coordinate &c, vector<Shortcuts::coordinate> &v) const {
	for (unsigned int i = 0; i < v.size(); i++) {
		if ((v[i].x == c.x) && v[i].y == c.y) {
			return true;
		}
	}
	return false;
}

