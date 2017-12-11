/*
 * HumanPlayer.cpp
 *
 *  leah orlin 313357725
 *  yair frank 203699566
 */

#include "HumanPlayer.h"

using namespace std;


HumanPlayer::~HumanPlayer() {
	// TODO Auto-generated destructor stub
}


HumanPlayer::HumanPlayer():Player (){}

HumanPlayer::HumanPlayer(char x): Player (x){}

void HumanPlayer::playTurn
        (Shortcuts::coordinate &coord, Shortcuts::coordVec &v,
         Board &b, GameLogic &gl, char &current, char &other, Client &cl, bool &firstMove) {
    int flag=0;
    int x, y;
    char c;
    Shortcuts::matrix board;
    Shortcuts::coordVec flips;
    Shortcuts::coordinate f;
    Shortcuts::coordVec::iterator it;
    board = b.getBoard();
    while (true) {
        if (!flag) {
            cout << sign << ": It's your move. Possible moves: " << endl;
            for (unsigned int i = 0; i < v.size(); i++) {

                cout << '(' << v[i].x << ',' << v[i].y << ") ";
            }
            cout << endl;
            cout << "Please enter your move row,column:" << endl;
        }
        cin >> x >> c >> y;
        //check for correct user input
        while (cin.fail() || c != ',') {
            cout << "Error, please enter move in requested format" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> x >> c >> y;
        }

        while (x < 1 || x > 8 || y < 1 || y > 8) {
            cout << "coordinates out of bounds. please submit your move again" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> x >> c >> y;
        }
        coord.x = x;
        coord.y = y;
        //make sure valid move was entered.
        if (!Player::checkValidInput(coord, v)) {
            cout << "please enter valid move" << endl;
            flag=1;
            continue;
        }else{
            break;
        }
    }
    //alter board
    b.enterMove(current, coord.x, coord.y);
    gl.flipTokens(current, coord.x - 1, coord.y - 1, board, flips);
    for (it = flips.begin(); it != flips.end(); it++) {
        f = *it;
        b.enterMove(current, f.x + 1, f.y + 1);
    }
    flips.clear();
    b.print();
    cout << current << " played (" << coord.x << ',' << coord.y << ')' << endl;
}
