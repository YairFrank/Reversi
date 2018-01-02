//
// Created by yair on 02/01/18.
//

#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "StartGameCommand.h"

void StartGameCommand::execute(vector <string> cd, int sid) {
    int n=write(sid, &cd , sizeof(cd));
    if (n == -1)
        throw runtime_error ("server is closed, dude");
    cout << "waiting for another player to connect..." << endl;
}

StartGameCommand::StartGameCommand(){}