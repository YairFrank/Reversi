//
// Created by yair on 27/11/17.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(): sign('X'), hasMoves(true) {
    vector<Shortcuts::coordinate> v;
}

Player::Player(char x) {
    sign = x;
    hasMoves = true;
    vector<Shortcuts::coordinate> v;
}

void Player::setHasMoves(bool x) {
    hasMoves = x;
}

bool Player::getHasMoves() const {
    return hasMoves;
}

char Player::getSign() const {
    return sign;
}
