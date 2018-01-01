//
// Created by yair on 08/12/17.
//

#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(): Player (){}

RemotePlayer::RemotePlayer(char x): Player (x){}

void RemotePlayer::playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec &v,
                            Board &b, GameLogic &gl, char &current, char &other, Client &client, bool &firstMove, Shortcuts::PlayMessage &play) {
    int flag = 0;
    int x, y;
    char c, open, close;
    Shortcuts::matrix board;
    Shortcuts::coordVec flips;
    Shortcuts::coordinate f;
    Shortcuts::coordVec::iterator it;
    board = b.getBoard();
    if ((current == 'O' && !firstMove) || current == 'X') {
        b.print();
        if (!firstMove) {
            if (play.x == -1)
                cout << "No move for " << other << endl;
            else
                cout << other << " played (" << play.x << ',' << play.y << ')' << endl;
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
                    cin >> play.str >> open >> play.x >> close >> open >> play.y >> close;
                    //check for correct user input
                    while (cin.fail() || open != '<' || close != '>') {
                        cout << "Error, please enter move in requested format" << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cin >> play.str >> open >> play.x >> close >> open >> play.y >> close;
                    }
                    while (play.x < 1 || play.x > 8 || play.y < 1 || play.y > 8) {
                        cout << "coordinates out of bounds. please submit your move again" << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cin >> play.str >> open >> play.x >> close >> open >> play.y >> close;
                    }
                    //make sure valid move was entered.
                    Shortcuts::coordinate coord{};
                    coord.x=play.x;
                    coord.y=play.y;
                    if (!Player::checkValidInput(coord, v)) {
                        cout << "please enter valid move" << endl;
                        flag = 1;
                        continue;
                    } else {
                        break;
                    }
                }
                try {
                    client.sendMessage(play);
                } catch (const char *msg) {
                    cout << "Failed to send coordinates to server. Reason: " << msg << endl;
                }
                b.enterMove(current, play.x, play.y);
                gl.flipTokens(current, play.x - 1, play.y - 1, board, flips);
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
            if (play.x == -1) {
                play.x = -2;
                play.y = -2;
            } else {
                //player had no moves available
                cout << "No possible moves for " << current
                     << ". Play passes back to the other player" << endl;
                try {
                    play.x = -1;
                    play.y = -1;
                    client.sendMessage(play);
                } catch (const char *msg) {
                    cout << "Failed to send coordinates to server. Reason: " << msg << endl;
                }
            }
        }
    }
    if(play.x!=-2){
        try {
            client.getMessage(play);
        } catch (const char *msg) {
            cout << "Failed to get coordinates from server. Reason: " << msg << endl;
        }
        if (play.x == -1)
            return;
        else {
            b.enterMove(other, play.x, play.y);
            gl.flipTokens(other, play.x - 1, play.y - 1, board, flips);
            for (it = flips.begin(); it != flips.end(); it++) {
                f = *it;
                b.enterMove(other, f.x + 1, f.y + 1);
            }
            flips.clear();
            firstMove = false;
        }
    }
}