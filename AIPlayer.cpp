//
// Created by yair on 27/11/17.
//

#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer(): Player (){}

AIPlayer::AIPlayer(char x): Player(x){}



//AIPlayer::AIPlayer(Board b): board(b), gl(GameLogic()){}

void AIPlayer::playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec v, Board &board) {
	GameLogic gl;
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

int AIPlayer::getOpponentsBestOption(Board b) {
	GameLogic gl;

	char oppSign = AIPlayer::getOppSign();
	vector<int> scores;
	int score = 0, bestScore = 0;
	Shortcuts::coordVec oppPlayerMoves, flips;
	Shortcuts::matrix dup;
	Board dupBoard;
	Shortcuts::coordVec::iterator it, flipIt;
	Shortcuts::coordinate possibleMove, flip;

	dupBoard = Board(b);
	dup = dupBoard.getBoard();
	gl.getValidMoves(oppSign, oppPlayerMoves, dup);
	//check which possible move will be most profitable for opponent
	for (it = oppPlayerMoves.begin(); it != oppPlayerMoves.end(); ++it) {
		//does this change board, or copy?????
		dupBoard = Board(b);
		dup = dupBoard.getBoard();
		possibleMove = *it;
		dupBoard.enterMove(oppSign,possibleMove.x, possibleMove.y);
		flips = gl.flipTokens(oppSign, possibleMove.x - 1, possibleMove.y - 1,
				dup);

		//flipping the tokens
		for (flipIt = flips.begin(); flipIt != flips.end(); ++flipIt) {
			flip = *flipIt;
			dupBoard.enterMove(oppSign, flip.x + 1, flip.y + 1);
		}

		// check score
		score = dupBoard.getScore(oppSign, sign);
		if (score > bestScore) {
			bestScore = score;
		}

	}
	return bestScore;
}

char AIPlayer::getOppSign() const {
	if (sign == 'O') {
		return 'X';
	}
	return 'O';
}




