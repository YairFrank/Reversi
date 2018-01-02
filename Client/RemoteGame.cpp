//
// Created by yair on 08/12/17.
//

#include <unistd.h>
#include <fstream>
#include "RemoteGame.h"
#include "RemotePlayer.h"
#include "CommandManager.h"
#include <iostream>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;
#define MAX 50

RemoteGame::RemoteGame() : b(Board()), gl(GameLogic()) {
}

void RemoteGame::play() {

    bool first = true;
    char char_array[MAX];
    string input, command;
    int numplay, waitmsg, n, num;
    char current, other;
    bool firstMove = true;
    char commandStr[MAX];
    istringstream iss;
    RemotePlayer *p;
    string IP;
    int port;
    ifstream inFile;
    inFile.open("infoclient.txt");
    inFile >> IP;
    inFile >> port;
    inFile.close();
    const char *ip = IP.c_str();
    Client cl(ip, port);
    try {
        cl.connectToServer();
    }
    catch (const char *msg) {
        cout << "Failed to connect to server. Reason:" << msg << endl;
    }

    while (true) {
        cout << "Choose one of the options below:" << endl << endl <<
             "to start a new game, please type - start my_game" << endl << endl <<
             "to see existing games, please type - list_games" << endl << endl <<
             "to join an existing game from the list, please type - join name_of_game_to_join" << endl;

        if (first) {
            cin.ignore();
            first = false;
        }

        getline(cin, input);
        iss.str(input);
        iss >> command;
        //if client wants to exit game
        if (command == "exit") {
            cout << "bye :)";
            return;
        }
        //check for valid input
        while (cin.fail() || (command != "start" && command != "join" && command != "list_games")) {
            cout << "Error, please enter valid option" << endl;
            cin.clear();
            //cin.ignore(256,'\n');
            getline(cin, input);
            iss.str(input);

            iss >> command;
        }


        strcpy(char_array, input.c_str());
        CommandManager::getInstance()->executeCommand(command, char_array, cl.getSocket());

    }
}


char RemoteGame::getWinner(char current, char other) const {
    return b.getMaxPoints(current, other);
}