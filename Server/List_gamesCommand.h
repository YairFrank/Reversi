//
// Created by leah on 25/12/17.
//

#ifndef ROOT_LIST_GAMESCOMMAND_H
#define ROOT_LIST_GAMESCOMMAND_H


#include "Command.h"

class List_gamesCommand: public Command {
public:
    List_gamesCommand();
    virtual void execute(vector <string> cd, int sid);
};


#endif //ROOT_LIST_GAMESCOMMAND_H
