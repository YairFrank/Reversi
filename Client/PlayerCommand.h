//
// Created by yair on 02/01/18.
//

#ifndef ROOT_PLAYERCOMMAND_H
#define ROOT_PLAYERCOMMAND_H

#include<vector>
#include<string>

using namespace std;

class PlayerCommand {
public:

    virtual void execute(vector <string> cd, int sid = 0) =0;

    virtual~PlayerCommand() {}
}
#endif //ROOT_PLAYERCOMMAND_H
