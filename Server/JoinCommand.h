//
// Created by leah on 25/12/17.
//

#ifndef ROOT_JOINCOMMAND_H
#define ROOT_JOINCOMMAND_H

#include "Command.h"
//typedef struct gameData{string name;int player1Socket; int player2socket;} gameData;
class JoinCommand: public Command {
public:
    JoinCommand();
    virtual void execute(vector <string> cd, int sid);
private:

    void runGame(string name, int player1Socket, int player2Socket);
    void assignSymbol(int clientSocket, int numPlayer) const;
    coordinate passMove(int clientSocket, coordinate oppMove, bool &firstMove);
    bool isWin(coordinate m);

};

#endif //ROOT_JOINCOMMAND_H
