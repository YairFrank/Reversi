//
// Created by leah on 02/01/18.
//

#include "CommandManager.h"
#include <iostream>
#include "GetListCommand.h"
#include "StartGameCommand.h"
#include "JoinGameCommand.h"
#include "GetListCommand.h"
#include<iostream>


using namespace std;


CommandManager::CommandManager() {
    commandsMap["start"] = new StartGameCommand();
    commandsMap["list_games"] = new GetListCommand();
    commandsMap["join"] = new JoinGameCommand();
}

CommandManager* CommandManager::instance = 0;
pthread_mutex_t CommandManager::lock;

CommandManager* CommandManager::getInstance() {
    if (instance == 0) {
        pthread_mutex_lock(&lock);
        if (instance == 0) {
            instance = new CommandManager();
        }
        pthread_mutex_unlock(&lock);
    }
    return instance;
}

void CommandManager::executeCommand(string command, char args[], int sid) {
    PlayerCommand *commandObj = commandsMap[command];

    commandObj->execute(args, sid);
}

CommandManager::~CommandManager() {
    map<string, PlayerCommand *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}