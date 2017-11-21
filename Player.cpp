//
// Created by yair on 05/11/17.
//

//Yair Frank 203699566

#include "Player.h"
Player::Player() =default;
Player::Player(char name, int count): name(name), count(count){}

int& Player::getCount(){
    return count;
}

char Player::getName(){
    return name;
}