/*
 * Player.cpp
 *
* leah orlin 313357725
 */

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(): sign('X'), hasMoves(true) {
	vector<Shortcuts::coordinate> v;
	moves  = v;
}


Player::Player(char x) {
	sign = x;
	hasMoves = true;
	vector<Shortcuts::coordinate> v;
	moves = v;
}

bool Player::hasOptions() const{
	return hasMoves;
}

void Player::playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec &v) {
	int x,y;
	char c;

	cout << sign << ": It's your move. possible moves are:" << endl;
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

void Player::setHasMoves(bool x) {
	hasMoves = x;
}

bool Player::getHasMoves() const {
	return hasMoves;
}

vector<Shortcuts::coordinate> Player::getMoves() const {
	return moves;
}

char Player::getSign() const {
	return sign;
}
