//
// Created by leah on 25/12/17.
//

#include "GamesList.h"
#include <iostream>
#include <unistd.h>

pthread_mutex_t gamesList_mutex;

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

GamesList::GamesList() {};

void GamesList::addGame(string name, int socket) {
    gameInfo game;
    vector<gameInfo>::iterator it;
    gameInfo gi;
    for (it = games.begin(); it != games.end(); ++it) {
        gi = *it;
        if (name == gi.game) {
            cout << "error, this game already exists" << endl;
            return;
        }
    }
    game.game = name;
    game.player1sock = socket;
    game.player2sock = 0;
    game.players = 1;

    //add mutex to avoid messes in game list (games being added\joined\erased simultaneously)
    pthread_mutex_lock(&gamesList_mutex);
    games.push_back(game);
    pthread_mutex_unlock(&gamesList_mutex);
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
    int i = 0;
    vector<gameInfo>::iterator it;
    gameInfo gi;
    for (it = games.begin(); it != games.end(); ++it) {

        gi = *it;
        if (gi.game == name) {
            //add mutex to avoid messes in game list (games being added\joined\erased simultaneously)
            pthread_mutex_lock(&gamesList_mutex);
            games.erase (games.begin()+i);
            pthread_mutex_unlock(&gamesList_mutex);
            return 1;
        }
        i++;
    }
    return 0;
}

void GamesList::display(int sid) {
    vector<gameInfo>::iterator it;
    vector<string> list;
    gameInfo gi;
    int numGames = 0;
    for (it = games.begin(); it != games.end(); ++it) {
        gi = *it;
        cout<<gi.game;
        if (gi.players == 1) {
            numGames++;
            list.push_back(gi.game);
        }
    }
    cout<<endl<<list[0]<<endl;
    int n=write(sid, &numGames, sizeof(numGames));
    if (n == -1)
        throw runtime_error ("error in writing my man");
    if (numGames == 0) {
        string str="none";
        int n=write(sid, &str, sizeof(str));
        if (n == -1)
            throw runtime_error ("error in writing my man");
    }else{
        for(int i=0; i<numGames;i++){
            int n=write(sid, list[i].c_str(), list[i].length());
            if (n == -1)
                throw runtime_error ("error in writing my man");
        }
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

void GamesList::getAllSockets(vector<int> &sockets) {
    vector<gameInfo>::iterator it;
    gameInfo gi;
    for (it = games.begin(); it != games.end(); ++it) {
        gi = *it;
        if (gi.player1sock != 0) {
            sockets.push_back(gi.player1sock);
        }
        if (gi.player2sock != 0) {
            sockets.push_back(gi.player2sock);
        }
    }

}
