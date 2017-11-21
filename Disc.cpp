//
// Created by yair on 05/11/17.
//

//Yair Frank 203699566

#include "Disc.h"

Disc::Disc() :disc ('0'){};
Disc::Disc(int row, int column):row (row), column (column){}
Disc::Disc (char disc, int row, int column): disc (disc), row (row), column (column)  {}
char Disc::getDisc () {
    return disc;
}

int Disc::getDiscRow() {
    return row;
}

int Disc::getDiscColumn() {
    return column;
}

void Disc::setDisc(char other) {
    disc=other;
}