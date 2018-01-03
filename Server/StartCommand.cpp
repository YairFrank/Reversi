//
// Created by yair on 24/12/17.
//

#include "Command.h"
#include "StartCommand.h"
#include "GamesList.h"
#include "CommandsManager.h"
#include<iostream>
#include <unistd.h>

void StartCommand::execute(vector <string> cd, int sid) {

    int status,n;
    GamesList* games = GamesList::getGamesList();
    cout<<"adding game " << cd[0] << endl;
    status = games->addGame(cd[0],sid);
    cout<<"startgame status: "<< status<<endl;

        //Notify client if succeeded to add game (if game already exists, will send 0 to indicate failure
        n=write(sid, &status , sizeof(status));
        if (n == -1) {
            throw runtime_error ("error writing to player socket");
    }

}

StartCommand::StartCommand(){}

