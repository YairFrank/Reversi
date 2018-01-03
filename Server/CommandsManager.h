//
// Created by yair on 24/12/17.
//

#ifndef ROOT_COMMANDSMANAGER_H
#define ROOT_COMMANDSMANAGER_H


#include <map>
#include "Command.h"


class CommandsManager {

public:
    /**
     * @return instance of game list
     */
    static CommandsManager *getInstance();

    /**
     * @param command to be executed.
     * @param args arguments necessary to implement command.
     * @param sid socket id of client
     */
    void executeCommand(string command, vector <string> args, int sid=0);

private:
    /**
     * default constructor
     */
    CommandsManager();

    /**
     * copy constructor
     */
    CommandsManager(const CommandsManager &);

    /**
     * destructor
     */
    ~CommandsManager();

    /**
     * map from string to command class
     */
    map<string, Command *> commandsMap;

    /**
     * instance of commandsManager
     */
    static CommandsManager *instance;

    /**
     * mutex to deal with critical points.
     */
    static pthread_mutex_t lock;
};


#endif //ROOT_COMMANDSMANAGER_H
