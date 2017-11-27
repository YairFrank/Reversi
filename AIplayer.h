//
// Created by yair on 27/11/17.
//

#ifndef REVERSI_AIPLAYER_H
#define REVERSI_AIPLAYER_H


#include "Shortcuts.h"
#include "Player.h"

class AIplayer: public Player {

public:
    AIplayer();
    AIplayer(char x);
    void playTurn(Shortcuts::coordinate &c) override;

private:
    char sign;
    bool hasMoves;
};


#endif //REVERSI_AIPLAYER_H
