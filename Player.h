//
// Created by yair on 27/11/17.
//

#ifndef REVERSI_PLAYER_H
#define REVERSI_PLAYER_H


#include "Shortcuts.h"

class Player {

public:
    Player();
    Player(char x);
    virtual void playTurn(Shortcuts::coordinate &c) =0;
    void setHasMoves(bool x);
    bool getHasMoves() const;
    char getSign() const;

private:
    char sign;
    bool hasMoves;
};


#endif //REVERSI_PLAYER_H
