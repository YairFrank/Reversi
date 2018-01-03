//
// Created by leah on 25/12/17.
//

#ifndef ROOT_LIST_GAMESCOMMAND_H
#define ROOT_LIST_GAMESCOMMAND_H


#include "Command.h"

class List_gamesCommand: public Command {
public:

    /**
     * constructor
     */
    List_gamesCommand();

    /**
     * execute command
     * @param cd client data relevan for command execution
     * @param sid client socket id
     */
    virtual void execute(vector <string> cd, int sid);
};


#endif //ROOT_LIST_GAMESCOMMAND_H
