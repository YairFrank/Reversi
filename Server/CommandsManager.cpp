//
// Created by yair on 24/12/17.
//

#include <iostream>
#include"CommandsManager.h"
#include "List_gamesCommand.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "GamesList.h"
#include<iostream>


using namespace std;


CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new List_gamesCommand();
    commandsMap["join"] = new JoinCommand();
}

CommandsManager* CommandsManager::instance = 0;
pthread_mutex_t CommandsManager::lock;

CommandsManager* CommandsManager::getInstance() {
    if (instance == 0) {
        pthread_mutex_lock(&lock);
        if (instance == 0) {
            instance = new CommandsManager();
        }
        pthread_mutex_unlock(&lock);
    }
    return instance;
}

void CommandsManager::executeCommand(string command, vector <string> cd, int sid) {
    Command *commandObj = commandsMap[command];

    cout<<"entered command manger with param " << cd[0] <<endl;
    commandObj->execute(cd, sid);

    pthread_exit(NULL);
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
