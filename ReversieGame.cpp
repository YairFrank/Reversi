/*
 * ReversieGame.cpp
 *
 *  Created on: Nov 11, 2017
* leah orlin 313357725
 */

#include "Shortcuts.h"
#include "ReversieGame.h"
#include "AIPlayer.h"

using namespace std;
//typedef vector<vector<char> > matrix;
//typedef struct coordinate {int x; int y;} coordinate;

ReversieGame::ReversieGame(int a) :
		gameOver(false), b(Board()), gl(GameLogic()), gameOption(a) {
}


void ReversieGame::play() {
    Player* p1;
    Player* p2;
    if (gameOption == 1){
        p1 = new HumanPlayer('X');
        p2 = new HumanPlayer('O');
    }
    if (gameOption == 2){
        p1 = new HumanPlayer('X');
        p2 = new AIPlayer('O');
    }
	Shortcuts::matrix board;
	Player* current = p1;
	Shortcuts::coordVec p1v;
	Shortcuts::coordVec p2v;
	Shortcuts::coordVec v, flips;
	Shortcuts::coordVec::iterator it;
	Shortcuts::coordinate c, f;
	char winner;
	//if exits while loop - neither players have moves. Game over.
	board = b.getBoard();
	b.print();
	while (b.hasFreeSpaces()
			&& (gl.hasValidMoves(p1->getSign(), p1v, board)
					|| gl.hasValidMoves(p2->getSign(), p2v, board))) {

		if (p2v.empty()) {
			gl.hasValidMoves(p2->getSign(), p2v, board);
		}
		if (!p1v.empty()) {
			p1->setHasMoves(true);
		}
		if (p1v.empty()){
			cout<< "no moves left for X" <<endl;
			p1->setHasMoves(false);
		}
		if (!p2v.empty()) {
			p2->setHasMoves(true);
		}
		if (p2v.empty())
		{
			cout<< "no moves left for O" <<endl;
			p2->setHasMoves(false);
		}

			//b.print();

			if (current->getHasMoves()) {
				if (current->getSign() == p1->getSign()) {
					v = p1v;
				} else {
					v = p2v;
				}

				current->playTurn(c,v,b);

				//make sure valid move was entered.
				while (!ReversieGame::checkValidInput(c, v)) {
					cout <<
					cout << "please enter valid move" << endl;
					current->playTurn(c,v,b);
				}

				//alter board
				b.enterMove(current->getSign(), c.x, c.y);
				flips = gl.flipTokens(current->getSign(), c.x - 1, c.y - 1,
						board);
				for (it = flips.begin(); it != flips.end(); it++) {
					f = *it;
					b.enterMove(current->getSign(), f.x + 1, f.y + 1);
				}

				//print board after update
				b.print();
				cout << current->getSign() << " played (" << c.x << ',' << c.y
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
		if (current->getSign() == p1->getSign()) {
			current = p2;
		} else {
			current = p1;
		}

	}
	// neither player has valid moves available. Game over.
	//announce winner

	winner = ReversieGame::getWinner(p1, p2);
	if (winner == 'c') {
		cout << "Game Over. You tied :-)" << endl;
	} else {
		cout << "Game Over. Winner is " << winner << " :)" << endl;
	}
    delete p1;
    delete p2;
}

char ReversieGame::getWinner(Player* p1, Player* p2) const {
	return b.getMaxPoints(p1->getSign(), p2->getSign());
}

bool ReversieGame::checkValidInput(Shortcuts::coordinate &c, vector<Shortcuts::coordinate> &v) const {
	for (unsigned int i = 0; i < v.size(); i++) {
		if ((v[i].x == c.x) && v[i].y == c.y) {
			return true;
		}
	}
	return false;
}

