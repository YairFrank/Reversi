//
// leah orlin 313357725
// yair frank 203699566

#include "Player.h"

using namespace std;

Player::Player(): sign('X'), hasMoves(true) {
}

Player::Player(char x):sign(x), hasMoves(true) {
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
