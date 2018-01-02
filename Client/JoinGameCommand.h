//
// Created by yair on 02/01/18.
//

#ifndef ROOT_JOINGAMECOMMAND_H
#define ROOT_JOINGAMECOMMAND_H


#include "PlayerCommand.h"

class JoinGameCommand : public PlayerCommand {
public:

    JoinGameCommand();


    virtual void execute(char char_array [], int sid);
};


#endif //ROOT_JOINGAMECOMMAND_H
