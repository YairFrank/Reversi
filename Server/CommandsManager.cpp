//
// Created by yair on 24/12/17.
//

#include"CommandsManager.h"
#include "List_gamesCommand.h"
#include "CloseCommand.h"
#include "StartCommand.h"
#include "PlayCommand.h"
#include "JoinCommand.h"
#include "GamesList.h"


using namespace std;


CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new List_gamesCommand();
    commandsMap["play"] = new PlayCommand();
    commandsMap["join"] = new JoinCommand();
    commandsMap["close"] = new CloseCommand();
    GamesList* gamesList = GamesList::getGamesList();

}


void CommandsManager::executeCommand(string command, clientData *cd, int sid) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(cd, sid);
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
