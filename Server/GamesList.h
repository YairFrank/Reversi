//
// Created by leah on 25/12/17.
//

#ifndef ROOT_GAMESLIST_H
#define ROOT_GAMESLIST_H

#include<vector>
#include<string>
using namespace std;


typedef struct gameInfo {string game ; int player1sock ; int player2sock; int players;} gameInfo;

/**
 * singleton class to enable keeping track of existing games and modifying the
 * list via the different threads
 */
class GamesList {

private:
    /* Here will be the instance stored. */
    static GamesList* gamesList;

    /* Private constructor to prevent instancing. */
    GamesList();

    vector<gameInfo> games;


public:
    /* Static access method. */
    static GamesList* getGamesList();

    /**
     * @return a list of all sockets currently participating in games (even if not active)
     */
    void getAllSockets(vector<int> &sockets);

    int addGame(string name, int socket);

    /**
     * joins a player to a game. Discriminates if there was already a player connected or not.
     * @param name game title.
     * @param socket joining players socket.
     * @return 0-if no such game exists. Otherwise- the first players socket.
     */
    int joinPlayer(string name,int socket);

    /**
     * removes a game from the list
     * @param name of the game
     * @return 1 if succeeded, 0-otherwise.
     */
    int removeGame(string name);

    /**
     * @param list updates list with games available to join
     */
    void getAvailableGames(vector<string> &list);

    /**
     * @param game name of game
     * @return opponents socket id
     */
    int getOpponent(string game,int sid);



};


#endif //ROOT_GAMESLIST_H
