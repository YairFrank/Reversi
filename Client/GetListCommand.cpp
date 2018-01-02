//
// Created by yair on 02/01/18.
//

#include <unistd.h>
#include <stdexcept>
#include <sys/param.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include "GetListCommand.h"

void GetListCommand::execute(char char_array [], int sid) {
    string input, buffer;
    istringstream iss;
    int n=write(sid, &char_array , sizeof(char_array));
    if (n == -1)
        throw runtime_error ("server is closed, dude");
    int numGames;
    char str [MAX];
    n=read(sid, &numGames, sizeof(numGames));
    if (n == -1)
        throw runtime_error ("server is closed, dude");

    for(int i=0;i<numGames;i++){
        n=read(sid, &str, sizeof(str));
        if (n == -1)
            throw runtime_error ("server is closed, dude");
        cout<<str<<", ";
    }
    cout<<endl;
    cin.ignore();
    getline(cin,input);
    buffer = input;
    iss.str(buffer);
    string command;
    iss >> command;
    while (cin.fail()|| (command != "start" && command != "join" && command != "list_games")) {
        cout << "Error, please enter valid option" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        getline(cin,input);
        buffer = input;
        iss.str(buffer);
        string command;
        iss >> command;
    }
    strcpy(char_array,input.c_str());
    cout << "sending string" << char_array <<endl;
    n=write(sid, &char_array , sizeof(char_array));
    if (n == -1)
        throw runtime_error ("server is closed, dude");
}

GetListCommand::GetListCommand() {}