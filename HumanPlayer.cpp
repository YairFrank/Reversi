/*
 * HumanPlayer.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: leah
 */

#include "HumanPlayer.h"
#include <iostream>

using namespace std;


HumanPlayer::~HumanPlayer() {
	// TODO Auto-generated destructor stub
}


HumanPlayer::HumanPlayer():Player (){}

HumanPlayer::HumanPlayer(char x): Player (x){}

void HumanPlayer::playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec v, Board &b) {
	int x,y;
	char c;

	cout << sign << ": It's your move." << endl;
	for (unsigned int i = 0; i < v.size(); i++) {

		cout << '(' << v[i].x << ',' << v[i].y << ") ";
	}
	cout << endl;
	cout << "Please enter your move row,column:" << endl;
	cin >> x >> c >> y;

	//check for correct user input
	while(cin.fail() || c != ',') {
	cout << "Error, please enter move in requested format" << endl;
	cin.clear();
	cin.ignore(256,'\n');
	cin >> x >> c >> y;
	}

	while (x < 1 || x > 8 || y < 1 || y > 8) {
		cout << "coordinates out of bounds. please submit your move again" << endl;
		cin.clear();
		cin.ignore(256,'\n');
		cin >> x >> c >> y;
	}
	coord.x = x;
	coord.y = y;
}
