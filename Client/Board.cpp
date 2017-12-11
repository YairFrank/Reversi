/*
 * leah orlin 313357725
 * yair frank 203699566
 */

#include "Board.h"


Board::Board() {
	vector<vector<char> > matrix(9);
	board = matrix;
	for ( int i = 0 ; i < 9 ; i++ ) {
		board[i].resize(9,' ');
	}

	//initial values.
	board[3][4] = 'X';
	board[4][3] = 'X';
	board[3][3] = 'O';
	board[4][4] = 'O';



	ConsoleDisplayer d;
	displayer = d;

}

Board::Board(Shortcuts::matrix b, ConsoleDisplayer d) {
	board = b;
	displayer = d;
}

Board::Board(int size) {

	Shortcuts::matrix matrix((size + 1), vector<char>(size + 1));
	board = matrix;

	for(int i = 0; i < size + 1;i++) {
		for (int j = 0; j< size + 1; j++) {
			board[i][j] = ' ';
		}
	}

	//initial values.
	board[(size / 2) - 1][size / 2] = 'X';
	board[size / 2][size / 2 - 1] = 'X';
	board[size / 2 - 1][size / 2 - 1] = 'O';
	board[size / 2][size / 2] = 'O';

	ConsoleDisplayer d;
	displayer = d;

}

Board::Board(const Board &b) {
	board = b.getBoard();
	displayer = b.getDisplayer();
}

void Board::print() const{
	displayer.display(board);
}

void Board::enterMove(char x, int i, int j) {
	board[i - 1][j - 1] = x;
}

bool Board::hasFreeSpaces() const {
	for (unsigned int i = 1; i < board.size(); i++)
	{
		for (unsigned int j = 1; j < board[i].size(); j++)
		{
			if (board[i][j] == ' ')
			{
				return true;
			}
		}
	}
	return false;
}

Shortcuts::matrix Board::getBoard() const {
	return board;
}

char Board::getMaxPoints(char a, char b) const {

	int pointsA = 0;
	int pointsB = 0;

	for (unsigned int i = 0; i < board.size(); i++)
	{
		for (unsigned int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == a)
			{
				pointsA++;
			}
			else if(board[i][j] == b)
			{
				pointsB++;
			}
		}
	}

	if (pointsA > pointsB) {
		return a;
	} else if (pointsA < pointsB) {
		return b;
	} else {
		//players tied.
		return 't';
	}
}



const ConsoleDisplayer& Board::getDisplayer() const {
	return displayer;
}

int Board::getScore(char a, char b) const {
	int pointsA = 0;
	int pointsB = 0;

	for (unsigned int i = 0; i < board.size(); i++)
	{
		for (unsigned int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == a)
			{
				pointsA++;
			}
			else if(board[i][j] == b)
			{
				pointsB++;
			}
		}
	}
	return (pointsA - pointsB);
}
