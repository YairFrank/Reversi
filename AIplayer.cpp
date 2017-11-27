/*
 * AIplayer.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: leah
 */

#include "AIplayer.h"
#include <iostream>

AIplayer::AIplayer(): Player('O') {}

AIplayer::AIplayer(char sigh): Player(sigh){}

AIplayer::AIplayer(Board b): board(b), gl(GameLogic()){}

AIplayer::~AIplayer() {
	// TODO Auto-generated destructor stub
}

void AIplayer::playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec v) {
	cout << "AI TURN" << endl;
	Board dup;
	Shortcuts::coordVec aiMoves = v;
	Shortcuts::coordVec::iterator it;
	Shortcuts::coordinate c;

	Shortcuts::matrix b = board.getBoard();
	Shortcuts::aiOption option, bestOption;
	vector <Shortcuts::aiOption> options;
	vector <Shortcuts::aiOption> :: iterator optionsIt;
	int minScore = b.size() ^2;	//maximum score possible

	for (it = aiMoves.begin(); it != aiMoves.end(); it++) {
		c = *it;
		option.move = c;
		//we want to check each possible move in a new board, as if the others were not tried first.
		dup = Board(board);
		dup.enterMove(sign, c.x, c.y);
		option.score = getOpponentsBestOption(dup);	//fill options
		options.push_back(option);
	}

	//find best option for AI player, after gaining data for all available options.
	for (optionsIt = options.begin(); optionsIt != options.end(); ++ optionsIt ) {
		option = *optionsIt;
		if (option.score < minScore) {
			minScore = option.score;
			bestOption = option;
		}
	}

	//set AI move to be the coordinates of the best move available
	coord.x = bestOption.move.x;
	coord.y = bestOption.move.y;


}

int AIplayer::getOpponentsBestOption(Board b) {
	char oppSign = AIplayer::getOppSign();
	vector<int> scores;
	int score = 0, bestScore = 0;
	Shortcuts::coordVec oppPlayerMoves, flips;
	Shortcuts::matrix dup;
	Board dupBoard;
	Shortcuts::coordVec::iterator it, flipIt;
	Shortcuts::coordinate possibleMove, flip;
	char s;

	s = AIplayer::getOppSign();
	dupBoard = Board(b);
	dup = dupBoard.getBoard();
	gl.getValidMoves(oppSign, oppPlayerMoves, dup);
	//check which possible move will be most profitable for opponent
	for (it = oppPlayerMoves.begin(); it != oppPlayerMoves.end(); ++it) {
		//does this change board, or copy?????
		dupBoard = Board(b);
		dup = dupBoard.getBoard();
		possibleMove = *it;
		dupBoard.enterMove(s,possibleMove.x, possibleMove.y);
		flips = gl.flipTokens(s, possibleMove.x - 1, possibleMove.y - 1,
				dup);

		//flipping the tokens
		for (flipIt = flips.begin(); flipIt != flips.end(); ++flipIt) {
			flip = *flipIt;
			dupBoard.enterMove(s, flip.x + 1, flip.y + 1);
		}

		// check score
		score = dupBoard.getScore(oppSign, sign);
		if (score > bestScore) {
			bestScore = score;
		}

	}
	return bestScore;



}

char AIplayer::getOppSign() const {
	if (sign == 'O') {
		return 'X';
	}
	return 'O';
}
