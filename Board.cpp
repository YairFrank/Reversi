/*
 * leah orlin 313357725
 */

#include "Board.h"


Board::Board() {
	vector<vector<char> > matrix(9);
	board = matrix;
	for ( int i = 0 ; i < 9 ; i++ ) {
		board[i].resize(9);
	}
	for(int i = 0; i < 9;i++) {
		for (int j = 0; j< 9; j++) {
			board[i][j] = ' ';
		}
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

Board::Board(int size, ConsoleDisplayer d) {
	vector<vector<char> > matrix(size);
	for (int i = 0 ; i < 8 ;i++ ) {
		matrix[i].resize(size);
	}

	board = matrix;
	displayer = d;

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
