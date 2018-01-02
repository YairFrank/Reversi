//
// Created by yair on 02/01/18.
//

#ifndef ROOT_GETLISTCOMMAND_H
#define ROOT_GETLISTCOMMAND_H


#include "PlayerCommand.h"

class GetListCommand : public PlayerCommand{
public:

    GetListCommand();


    virtual void execute(char char_array [], int sid);
};


#endif //ROOT_GETLISTCOMMAND_H
