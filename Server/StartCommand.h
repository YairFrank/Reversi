//
// Created by leah on 25/12/17.
//

#ifndef ROOT_STARTCOMMAND_H
#define ROOT_STARTCOMMAND_H


#include "Command.h"

class StartCommand: public Command {
public:

    /**
     * constructor
     */
    StartCommand();


    /**
     * execute command
     * @param cd  client data relevant for execution of command
     * @param sid client socket id
     */
    virtual void execute(vector <string> cd, int sid);

};


#endif //ROOT_STARTCOMMAND_H
