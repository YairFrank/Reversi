//
// Created by yair on 27/11/17.
//

#include "AIPlayer.h"
#include "Shortcuts.h"
#include <iostream>

using namespace std;

AIPlayer::AIPlayer(): Player (){}

AIPlayer::AIPlayer(char x): Player (x){}

void AIPlayer::playTurn(Shortcuts::coordinate &coord) {
    int x,y;
    char c;

    cout << "Please enter your move row,column:" << endl;
    cin >> x >> c >> y;

    //check for correct user input
    while(cin.fail() || c != ',') {
        cout << "Error, please enter move in requested format" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> x >> c >> y;
    }

    while (x < 1 || x > 8 || y < 1 || y > 8) {
        cout << "coordinates out of bounds. please submit your move again" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> x >> c >> y;
    }
    coord.x = x;
    coord.y = y;
}
