//
// Created by yair on 24/12/17.
//

#ifndef ROOT_COMMANDSMANAGER_H
#define ROOT_COMMANDSMANAGER_H


#include <map>
#include "Command.h"


class CommandsManager {

public:

    CommandsManager();
    ~CommandsManager();
    void executeCommand(string command, clientData *cd, int sid);

private:

    map<string, Command *> commandsMap;


};


#endif //ROOT_COMMANDSMANAGER_H
