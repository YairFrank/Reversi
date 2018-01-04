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
#include <cstdlib>
#include <limits>

using namespace std;
#define MAXLEN 50

RemoteGame::RemoteGame() : b(Board()), gl(GameLogic()) {
}

void RemoteGame::initialize() {

    bool first = true, played = false,valid;
    char char_array[MAXLEN];
    string input, command;
    int n, numCommand = 0, status;

    RemotePlayer *p;
    string IP;
    int port, flag = 0;  //for getLine func correctness;
    ifstream inFile;
    inFile.open("infoclient.txt");
    inFile >> IP;
    inFile >> port;
    inFile.close();
    const char *ip = IP.c_str();
    Client client(ip, port);

    while (true) {
        cl = client;
        try {
            cl.connectToServer();
        }
        catch (const char *msg) {
            cout << "server closed, sorry";
            exit(0);
        }
        cout << "Choose one of the options below:" << endl << endl <<
             "to start a new game, please type - start my_game" << endl << endl <<
             "to see existing games, please type - list_games" << endl << endl <<
             "to join an existing game from the list, please type - join name_of_game_to_join" << endl;

        if (first || played) {
            cin.ignore();
            first = false;
        }

        //get command from client
        cin.clear();
        getline(cin, input);
        istringstream iss(input);
        string command;
        iss >> command;
        //if client wants to exit game
        if (command == "exit") {
            cout << "bye :)";
            return;
        }

        while(!checkValid(command)) {
            cin.clear();
            getline(cin, input);
            cout<<"input: "<<input<<endl;
            iss.str(input);
            string command;
            iss >> command;
            cout<<"command: "<<command<<endl;
            valid = checkValid(command);
            if (valid) {
                break;
            }
        }

        //write command to server
        strcpy(char_array, input.c_str());
        n=write(cl.getSocket(), &char_array , sizeof(char_array));
        if (n == -1 || n == 0) {
            cout << "server closed, sorry";
            exit(0);
        }


        if (command == "start") {
            //get information from server if command succeeded - if not, we will get 0 from server
            n=read(cl.getSocket(), &status, sizeof(status));
            if (n == -1 || n == 0) {
                cout << "server closed, sorry";
                exit(0);
            }

            if (status == 0) {
                cout << "start failed, game already exists"<< endl;
                continue;
            }

            //otherwise, game was initialized. Now wait for another player to connect before starting to play
            cout <<"game initialized, waiting for another player to connect..."<<endl;
            RemoteGame::play();

        } else if (command == "join"){

            //necessary for cleaing console before reading next command from client
            played = true;
            //start playing a previously initilized game
            RemoteGame::play();
        } else {
            //player asked to get a list of games
            RemoteGame::receiveList();
        }

    }
}

bool RemoteGame::checkValid(string command) {
    if ((command != "start" && command != "join" && command != "list_games")) {
        cout << "Error, please enter valid option: "<<command << endl;
        return false;
    }
    return true;
}


void RemoteGame::play() {
    int numplay, n;
    char current, other;
    bool firstMove=true;
    RemotePlayer* p;
    Shortcuts::matrix board;
    Shortcuts::coordVec pv;
    Shortcuts::coordinate c;
    char winner;

    //get information from server that client about player symbol
    n=read(cl.getSocket(), &numplay, sizeof(numplay));
    if (n == -1 || n == 0) {
        cout << "server closed, sorry";
        exit(0);
    }

    if (numplay == 0) {
        //server sends 0 upon failure to join unexisiting game
        cout << "join failed, no such game exists"<< endl;
        return;
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


    //game logic from previous code planning left unchanged. if exits while loop - neither players have moves. Game over.
    while (b.hasFreeSpaces()&&c.x!=-2)
        p->playTurn(c, pv, b, gl, current, other, cl, firstMove);
    // neither player has valid moves available. Game over.
    //announce winner
    winner = RemoteGame::getWinner(current, other);
    if (winner == 't') {
        cout << "Game Over. You tied :-)" << endl;
    } else {
        cout << "Game Over. Winner is " << winner << " :)" << endl;
    }
    try{
        c.x=-3;
        c.y=-3;
        cl.sendCoord(c);
    }catch (const char *msg) {
        cout << "server closed, sorry";
        exit(0);
    }
    delete p;
}

char RemoteGame::getWinner(char current, char other) {
    return b.getMaxPoints(current, other);
}

void RemoteGame::receiveList() {
    int n,numGames, bufint;
    string input, buffer;
    istringstream iss;
    char str [MAXLEN];
    //get number of games from server
    n=read(cl.getSocket(), &bufint, sizeof(bufint));
    if (n == -1 || n == 0) {
        cout << "server closed, sorry";
        exit(0);
    }

    numGames = bufint;
    if (numGames == 0) {
        cout<<"no games to join"<<endl;
    }
    for(int i=0;i<numGames;i++){
        n=read(cl.getSocket(), &str, sizeof(str));
        if (n == -1 || n == 0) {
            //display the available games on client console
            cout << "server closed, sorry";
            exit(0);
        }
        cout<<str;
        if (numGames != 1) {
            cout << ", ";
        }
    }
    cout<<endl;

}
