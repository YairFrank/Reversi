//
// Created by yair on 08/12/17.
//

#ifndef ROOT_REMOTEGAME_H
#define ROOT_REMOTEGAME_H


#include "GameLogic.h"
#include "Board.h"
#include "Game.h"
#include "Client.h"

class RemoteGame : public Game {
public:
    /**
	 * default constructor.
	 */
    RemoteGame();

    /**
     * play the game.
     */
    void play();

    /**
     * initialize game by sending command to server
     */
    void initialize();

    /**
     * @return the sign of the winner (t if tied).
     */
    char getWinner(char current, char other);


private:

    Board b;

    GameLogic gl;

    Client cl;

    /**
     * get the list of games from server
     */
    void receiveList();

    /**
     * @return check if command is valid
     */
    bool checkValid(string command);
};


#endif //ROOT_REMOTEGAME_H
