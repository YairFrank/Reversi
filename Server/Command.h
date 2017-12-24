//
// Created by yair on 24/12/17.
//

#ifndef ROOT_COMMAND_H
#define ROOT_COMMAND_H

#include<vector>
#include<string>

using namespace std;

class Command {

public:

    virtual void execute(vector<string> args) =0;
    virtual~Command() {}
};

#endif //ROOT_COMMAND_H