//
// Created by yair on 24/12/17.
//

#ifndef ROOT_COMMAND_H
#define ROOT_COMMAND_H

#include<vector>
#include<string>
#include "GamesList.h"
//typedef struct clientData {string command ; string name; int x; int y;} clientData;
typedef struct coordinate {int x; int y;} coordinate;
using namespace std;

class Command {

public:

    virtual void execute(vector <string> cd, int sid=0) =0;
    virtual~Command() {}
};

#endif //ROOT_COMMAND_H