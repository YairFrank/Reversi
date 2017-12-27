//
// Created by leah on 25/12/17.
//

#ifndef ROOT_JOINCOMMAND_H
#define ROOT_JOINCOMMAND_H

#include "Command.h"

class JoinCommand: public Command {
public:
    JoinCommand();
    virtual void execute(clientData *cd, int sid);
};

#endif //ROOT_JOINCOMMAND_H
