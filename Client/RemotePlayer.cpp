//
// Created by yair on 08/12/17.
//

#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(): Player (){}

RemotePlayer::RemotePlayer(char x): Player (x){}

void RemotePlayer::playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec &v,
                            Board &b, GameLogic &gl, char &current, char &other, Client &client, bool &firstMove) {
    int flag = 0;
    int x, y;
    char c;
    Shortcuts::matrix board;
    Shortcuts::coordVec flips;
    Shortcuts::coordinate f;
    Shortcuts::coordVec::iterator it;
    board = b.getBoard();

    if ((current == 'O' && !firstMove) || current == 'X') {
        b.print();
        if (!firstMove) {
            if (coord.x == -1)
                cout << "No move for " << other << endl;
            else
                cout << other << " played (" << coord.x << ',' << coord.y << ')' << endl;
        }
        if (gl.hasValidMoves(current, v, board)) {
            if (!v.empty()) {
                setHasMoves(true);
            }
            if (v.empty()) {
                setHasMoves(false);
            }
            //set possible moves vector to be the either the vector of player1 or player 2.
            if (getHasMoves()) {
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
                        flag = 1;
                        continue;
                    } else {
                        break;
                    }
                }
                try {
                    client.sendCoord(coord);
                } catch (const char *msg) {
                    cout << "Failed to send coordinates to server. Reason: " << msg << endl;
                }
                b.enterMove(current, coord.x, coord.y);
                gl.flipTokens(current, coord.x - 1, coord.y - 1, board, flips);
                for (it = flips.begin(); it != flips.end(); it++) {
                    f = *it;
                    b.enterMove(current, f.x + 1, f.y + 1);
                }
                flips.clear();
                b.print();
                cout << "Waiting for other player's move..." << endl;
                v.clear();
                board = b.getBoard();
            }
        } else {
            if (coord.x == -1) {
                coord.x = -2;
                coord.y = -2;
            } else {
                //player had no moves available
                cout << "No possible moves for " << current
                     << ". Play passes back to the other player" << endl;
                try {
                    coord.x = -1;
                    coord.y = -1;
                    client.sendCoord(coord);
                } catch (const char *msg) {
                    cout << "Failed to send coordinates to server. Reason: " << msg << endl;
                }
            }
        }
    }
    if(coord.x!=-2){
        try {
            client.getCoord(coord);
        } catch (const char *msg) {
            cout << "Failed to get coordinates from server. Reason: " << msg << endl;
        }
        if (coord.x == -1)
            return;
        else {
            b.enterMove(other, coord.x, coord.y);
            gl.flipTokens(other, coord.x - 1, coord.y - 1, board, flips);
            for (it = flips.begin(); it != flips.end(); it++) {
                f = *it;
                b.enterMove(other, f.x + 1, f.y + 1);
            }
            flips.clear();
            firstMove = false;
        }
    }
}