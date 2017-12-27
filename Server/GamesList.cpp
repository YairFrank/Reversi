//
// Created by leah on 25/12/17.
//

#include "GamesList.h"
#include "algorithm"
#include <iostream>

/* Null, because instance will be initialized on demand. */

//check where to add mutex!!
GamesList* GamesList::gamesList = 0;

GamesList* GamesList::getGamesList()
{
    if (gamesList == 0)
    {
        gamesList = new GamesList();
    }

    return gamesList;
}

GamesList::GamesList() = default;

void GamesList::addGame(string name, int socket) {
    vector<gameInfo>::iterator it;
    gameInfo gi;
    for (it = games.begin(); it != games.end(); ++it) {
        gi = *it;
        if (name == gi.game) {
            cout << "error, this game already exists" << endl;
            return;
        }
    }
    gameInfo game{name, socket, 0, 1};

    //add mutex!!!!!
    games.push_back(game);
}


void GamesList::removeSocket(int socket) {
    vector<gameInfo>::iterator it;
    gameInfo gi;
    for (it = games.begin(); it != games.end(); ++it) {
        gi = *it;
        if (gi.player1sock == socket) {
            gi.player1sock = 0;
            gi.players--;
        }
        if (gi.player2sock == socket) {
            gi.player2sock = 0;
            gi.players--;
        }
    }
}

//make sure bug-free
int GamesList::removeGame(string name) {
    vector<gameInfo>::iterator it;
    gameInfo gi;
    for (it = games.begin(); it != games.end(); ++it) {
        gi = *it;
        if (gi.game == name) {
            games.erase(remove(games.begin(), games.end(), gi), games.end());
            return 1;
        }
    }
    return 0;
}

void GamesList::display() {
    vector<gameInfo>::iterator it;
    gameInfo gi;
    int numGames = 0;
    cout << "available games: ";
    for (it = games.begin(); it != games.end(); ++it) {
        gi = *it;
        if (gi.players == 1) {
            numGames++;
            cout <<gi.game << ", ";
        }
    }
    if (numGames == 0) {
        cout << "none";
    }
    cout << endl;
}

int GamesList::getOpponent(int socket) {
    vector<gameInfo>::iterator it;
    gameInfo gi;
    for (it = games.begin(); it != games.end(); ++it) {
        gi = *it;
        if (gi.player1sock == socket) {
            return gi.player2sock;
        } else if(gi.player2sock == socket) {
            return gi.player1sock;
        }
    }

    //finished iterating over games, and players socket was not found participating in any game
    return 0;
}
