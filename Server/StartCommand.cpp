//
// Created by yair on 24/12/17.
//

#include "Command.h"
#include "StartCommand.h"
#include "GamesList.h"
#include "CommandsManager.h"

void StartCommand::execute(vector <string> cd, int sid) {

    //args holds all
    GamesList* games = GamesList::getGamesList();

    games->addGame(cd[0],sid);

    //close the thread!!
}

StartCommand::StartCommand(){}

