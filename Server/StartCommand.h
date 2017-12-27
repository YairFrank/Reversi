//
// Created by leah on 25/12/17.
//

#ifndef ROOT_STARTCOMMAND_H
#define ROOT_STARTCOMMAND_H


#include "Command.h"

class StartCommand: public Command {
public:

    StartCommand();


    virtual void execute(clientData *cd, int sid);

};

#endif //ROOT_JOINCOMMAND_H


#endif //ROOT_STARTCOMMAND_H
