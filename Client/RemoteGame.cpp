//
// Created by yair on 08/12/17.
//

#include <unistd.h>
#include <fstream>
#include "RemoteGame.h"
#include "RemotePlayer.h"
#include <iostream>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;
#define MAX 50

RemoteGame::RemoteGame() : b(Board()), gl(GameLogic()) {
}

void RemoteGame::play() {
    char char_array [MAX];
    string input, buffer;
    int numplay, waitmsg, n, num;
    char current, other;
    bool firstMove=true;
    char commandStr [MAX];
    istringstream iss;
    RemotePlayer* p;
    string IP;
    int port;
    ifstream inFile;
    inFile.open("infoclient.txt");
    inFile >> IP;
    inFile >> port;
    inFile.close();
    const char* ip= IP.c_str();
    Client cl(ip, port);
    try {
        cl.connectToServer();
    }
    catch (const char *msg) {
        cout << "Failed to connect to server. Reason:" << msg << endl;
    }


    cout<<"Choose one of the options below:"<<endl<<endl<<
        "to start a new game, please type - start my_game"<<endl<<endl<<
        "to see existing games, please type - list_games" <<endl<<endl<<
        "to join an existing game from the list, please type - join name_of_game_to_join"<<endl;

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

//    //check valid input
//    string str(char_array);
//    iss.str(str);
//    string command;
//    iss >> command;
//    if (command == "list_games") {
//        cout<<"yay!"<<endl;
//    }


    //check for correct user input


    //cout << "sending string" << char_array <<endl;

    //Sending the command

    //n=write(cl.getSocket(), &char_array , sizeof(char_array));
    //if (n == -1)
        //throw runtime_error ("server is closed, dude");



    if(command=="list_games"){
    }

    if(command=="start"){
    }
    if (command=="join"){
    }


    //waitmsg=numGames;


    //get information from server that client should wait for another player to connect/player symbol
    //n=read(cl.getSocket(), &waitmsg, sizeof(waitmsg));
    //if (n == -1)
    //    throw runtime_error ("server is closed, dude");
    /*if (waitmsg == -1) {
        cout << "waiting for another player to connect..." << endl;
        //get information from server about player's symbol
        n=read(cl.getSocket(), &num, sizeof(num));
        if (n == -1)
            throw runtime_error ("server is closed, dude");
    }

    //in case current client was not first to connect.
    if (waitmsg == -1)
        numplay = 1;
    else {
        numplay=2;
    }*/

}