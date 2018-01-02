//
// Created by leah on 02/01/18.
//

#ifndef ROOT_COMMANDMANAGER_H
#define ROOT_COMMANDMANAGER_H

#include <map>
#include "PlayerCommand.h"
class CommandManager {

public:
    static CommandManager *getInstance();
    void executeCommand(string command, char args[], int sid=0);

private:
    CommandManager();
    CommandManager(const CommandManager &);
    ~CommandManager();
    map<string, PlayerCommand *> commandsMap;
    static CommandManager *instance;
    static pthread_mutex_t lock;


};


#endif //ROOT_COMMANDMANAGER_H
