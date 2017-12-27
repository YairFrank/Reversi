//
// Created by leah on 25/12/17.
//

#ifndef ROOT_CLOSECOMMAND_H
#define ROOT_CLOSECOMMAND_H


#include "Command.h"

class CloseCommand: public Command {
public:
    CloseCommand();
    virtual void execute(clientData *cd, int sid);
};


#endif //ROOT_CLOSECOMMAND_H
