//
// Created by yair on 27/11/17.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(): sign('X'), hasMoves(true) {
}

Player::Player(char x) {
    sign = x;
    hasMoves = true;
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
