//
// Created by yair on 05/11/17.
//
//
// Created by yair on 05/11/17.
//

//Yair Frank 203699566

#ifndef TARGIL1_PLAYER_H
#define TARGIL1_PLAYER_H

using namespace std;

#include <string>
#include <vector>
#include "Disc.h"
#include "Board.h"

class Player {
public:
    /**
     * Default constructor
     */
    Player();
    /**
     * Constructor
     * @param name
     * @param count
     */
    Player (char name, int count);
    /**
     * Getter of discs' amount.
     * @return
     */
    int& getCount();
    /**
     * Getter of player's sign.
     * @return
     */
    char getName();
private:
    char name;
    int count;

};


#endif //TARGIL1_PLAYER_H
