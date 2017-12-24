//
// Created by yair on 24/12/17.
//

#ifndef ROOT_PRINTCOMMAND_H
#define ROOT_PRINTCOMMAND_H

#include"Command.h"
#include<iostream>
class PrintCommand: public Command {

public:

    virtual void execute(vector<string> args) {
        for (int i = 0; i < args.size(); i++) {
            cout << args[i] << " ";
        }
        cout << endl;
    }
};

#endif //ROOT_PRINTCOMMAND_H
