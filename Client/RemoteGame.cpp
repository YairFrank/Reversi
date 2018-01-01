//
// Created by yair on 08/12/17.
//

#include <unistd.h>
#include <fstream>
#include <cstring>
#include "RemoteGame.h"
#include "RemotePlayer.h"

using namespace std;
#define MAX 50

RemoteGame::RemoteGame() : b(Board()), gl(GameLogic()) {
}

void RemoteGame::play() {
    int numplay, waitmsg, n, num;
    char current, other;
    bool firstMove=true;
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
    struct Message {string str1; string str2;};
    Message message;
    char str [MAX];
    cout<<"Choose one of the options below:"<<endl<<endl<<
        "to start a new game, please type - start my_game"<<endl<<endl<<
        "to see existing games, please type - list_games" <<endl<<endl<<
        "to join an existing game from the list, please type - join name_of_game_to_join"<<endl;
    cin>>str;
    //cin>>message.str1>>open>>message.str2>>close;
    //check for correct user input
    while (cin.fail()) {
        cout << "Error, please enter move in requested format" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        //cin>>message.str1>>open>>message.str2>>close;
        cin>>str;
    }
    
    n=write(cl.getSocket(), &str , sizeof(str));
    if (n == -1)
        throw runtime_error ("server is closed, dude");
    char key[MAX]="list_games";
    if(strcmp(key, str) != 0){
        int numGames;
        string game;
        n=read(cl.getSocket(), &numGames, sizeof(numGames));
        cout<<numGames<<endl;
        if (n == -1)
            throw runtime_error ("server is closed, dude");
        cout<<"available games: ";
        for (int i=0; i<numGames;i++){
            n=read(cl.getSocket(), &game, sizeof(game));
            if (n == -1)
                throw runtime_error ("server is closed, dude");
            cout<<game<<", ";
        }
    }
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
    message.str1="close";
    n=write(cl.getSocket(), &message, 100);
    if (n == -1)
        throw runtime_error ("server is closed, dude");
    delete p;
}

char RemoteGame::getWinner(char current, char other) const {
    return b.getMaxPoints(current, other);
}