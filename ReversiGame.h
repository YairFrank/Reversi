//
// Created by yair on 05/11/17.
//

//Yair Frank 203699566


#ifndef TARGIL1_REVERSIGAME_H
#define TARGIL1_REVERSIGAME_H
#include <string>
#include "Board.h"
#include "Disc.h"

class ReversiGame {
public:
    /**
     * Constructor
     */
    ReversiGame ();
    /**
     * Gettet of the rival, according to the current player.
     * @param p
     * @param p1
     * @param p2
     * @return
     */
    Player & getRival(Player &p, Player &p1, Player &p2);
    /**
     * Validating that the input are numbers.
     * @return
     */
    int getNumberFromUser();
    /**
     * The process of the game.
     */
    void game();
private:
};


#endif //TARGIL1_REVERSIGAME_H
