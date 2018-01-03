//
// Created by yair on 02/01/18.
//

#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "StartGameCommand.h"

void StartGameCommand::execute(char char_array [], int sid) {
    int num;
    int n=write(sid, &char_array , sizeof(char_array));
    if (n == -1)
        throw runtime_error ("server is closed, dude");

    n=read(sid, &num, sizeof(num));
    if (n == -1)
        throw runtime_error ("server is closed, dude");
    if(num==0) {
        cout << "Game already exists";
        return;
    }
    if(num==1) {
        cout << "Game initialized" << endl;
        cout << "waiting for another player to connect..." << endl;

    }

}

StartGameCommand::StartGameCommand(){}