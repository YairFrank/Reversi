//
// Created by leah on 25/12/17.
//

#include "List_gamesCommand.h"
#include "Command.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

List_gamesCommand::List_gamesCommand() {}

void List_gamesCommand::execute(vector <string> cd, int sid) {
    cout<<"enterd listGamescommand server"<<endl;
    int numGames = 0;
    GamesList* games = GamesList::getGamesList();
    vector<string> list = games->getAvailableGames();
    vector<string>::iterator it;
    string game;

    //check how many games there are
    for (it = list.begin(); it != list.end(); ++it) {
        numGames++;
    }

    //inform client of number of games to expect
    int n=write(sid, &numGames, sizeof(numGames));
    if (n == -1) {
        throw runtime_error("error in writing my number of games");
    }

    //write games to client
    for (it = list.begin(); it != list.end(); ++it) {
        game = *it;
        int n=write(sid, &game, sizeof(game));
        if (n == -1) {
            throw runtime_error("error in writing game name");
        }
    }


}