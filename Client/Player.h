// leah orlin 313357725
// yair frank 203699566

#ifndef REVERSI_PLAYER_H
#define REVERSI_PLAYER_H
#include "Shortcuts.h"
#include "Board.h"
#include "Client.h"

class Player {

public:
    Player();
    Player(char x);
    virtual void playTurn(Shortcuts::coordinate &c, Shortcuts::coordVec &v,
                          Board &b, GameLogic &gl, char &current, char &other, Client &cl, bool &firstMove) =0;
    void setHasMoves(bool x);
    bool getHasMoves() const;
    char getSign() const;
    bool checkValidInput(Shortcuts::coordinate &c, vector<Shortcuts::coordinate> &v) const;

protected:
    char sign;
    bool hasMoves;
};

#endif //REVERSI_PLAYER_H
