//
// Created by yair on 24/12/17.
//

#ifndef ROOT_COMMANDSMANAGER_H
#define ROOT_COMMANDSMANAGER_H


#include <map>
#include "Command.h"


class CommandsManager {

public:
    static CommandsManager *getInstance();
    void executeCommand(string command, vector <string> cd, int sid=0);

private:
    CommandsManager();
    CommandsManager(const CommandsManager &);
    ~CommandsManager();
    map<string, Command *> commandsMap;
    static CommandsManager *instance;
    static pthread_mutex_t lock;
};


#endif //ROOT_COMMANDSMANAGER_H
