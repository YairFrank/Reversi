//
// Created by leah on 25/12/17.
//

#ifndef ROOT_PLAYCOMMAND_H
#define ROOT_PLAYCOMMAND_H

#include "Command.h"

class PlayCommand: public Command {
public:
    PlayCommand();


    void execute(clientData *cd, int sid);

};

#endif //ROOT_PLAYCOMMAND_H
