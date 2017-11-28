//
// Created by yair on 28/11/17.
//

#ifndef REVERSI_PLAYER_H
#define REVERSI_PLAYER_H
#include "Shortcuts.h"
#include "Board.h"

class Player {

public:
    Player();
    Player(char x);
    virtual void playTurn(Shortcuts::coordinate &c, Shortcuts::coordVec v, Board &b) =0;
    void setHasMoves(bool x);
    bool getHasMoves() const;
    char getSign() const;

protected:
    char sign;
    bool hasMoves;
};

#endif //REVERSI_PLAYER_H
