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
    string input;
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
    strcpy(char_array,input.c_str());

    //check valid input
    string str(commandStr);
    iss.str(str);
    string command;
    iss >> command;



    //check for correct user input

    while (cin.fail()|| command != "start" || command != "join" || command != "list_games") {
        cout << "Error, please enter valid option" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        getline(cin,input);
        strcpy(char_array,input.c_str());

        //check valid input
        string str(commandStr);
        iss.str(str);
        string command;
        iss >> command;
    }
    cout << "sending string" << str <<endl;
    n=write(cl.getSocket(), &str , sizeof(str));
    if (n == -1)
        throw runtime_error ("server is closed, dude");
    //get information from server that client should wait for another player to connect/player symbol
    n=read(cl.getSocket(), &waitmsg, sizeof(waitmsg));
    if (n == -1)
        throw runtime_error ("server is closed, dude");
    if (waitmsg == 3) {
        cout << "waiting for another player to connect..." << endl;
        //get information from server about player's symbol
        n=read(cl.getSocket(), &num, sizeof(num));
        if (n == -1)
            throw runtime_error ("server is closed, dude");
    }

    //in case current client was not first to connect.
    if (waitmsg != 3)
        numplay = waitmsg;
    else {
        numplay=num;
    }


    if (numplay==1){
        p = new RemotePlayer('X');
        current='X';
        other='O';
        cout<<"You are X"<<endl;
    }
    if (numplay==2) {
        p = new RemotePlayer('O');
        current='O';
        other='X';
        cout<<"You are O"<<endl;
        cout << "Waiting for other player..." << endl;
    }
    Shortcuts::matrix board;
    Shortcuts::coordVec pv;
    Shortcuts::coordinate c;
    Shortcuts::PlayMessage play;
    char winner;
    //if exits while loop - neither players have moves. Game over.
    while (b.hasFreeSpaces()&&play.x!=-2)
        p->playTurn(c, pv, b, gl, current, other, cl, firstMove, play);
    // neither player has valid moves available. Game over.
    //announce winner
    winner = RemoteGame::getWinner(current, other);
    if (winner == 't') {
        cout << "Game Over. You tied :-)" << endl;
    } else {
        cout << "Game Over. Winner is " << winner << " :)" << endl;
    }
    //message.str1="close";
    //n=write(cl.getSocket(), &message, 100);
    if (n == -1)
        throw runtime_error ("server is closed, dude");
    delete p;
}

char RemoteGame::getWinner(char current, char other) const {
    return b.getMaxPoints(current, other);
}