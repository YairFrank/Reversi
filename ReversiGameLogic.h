//
// Created by yair on 05/11/17.
//

//Yair Frank 203699566

#ifndef TARGIL1_REVERSIGAMELOGIC_H
#define TARGIL1_REVERSIGAMELOGIC_H
#include "Player.h"
#include "Disc.h"
#include <vector>
#include <iostream>

class ReversiGameLogic {
public:
    /**
     * Constructor
     * @param m
     * @param size
     */
    ReversiGameLogic (Disc** m, int size, vector<Disc>& choise);
    /**
     * Updating a new list of possible moves.
     * @param current
     * @param other
     * @param list
     */
    void updateList(char current, char other, vector <Disc>& list);
    /**
     * Adding a new disc to the board, and switching all the rival's relevant discs.
     * @param p1
     * @param p2
     * @param i
     * @param j
     * @param b
     */
    void addAndChange (Player& p1, Player &p2, int& i, int& j, Board& b);
    /**
     * Switching between players after every turn.
     * @param p
     * @param p1
     * @param p2
     * @return
     */
    Player * switchPlayer(Player* p, Player& p1, Player &p2);
    /**
     * Adding every possible move to the list.
     * @param i
     * @param j
     * @param v
     */
    void options(int i, int j, vector<Disc>& v);
    /**
     * Getter of the choise of previous player.
     * @return
     */
    vector <Disc>& getChoise();
private:
    Disc** m;
    int size;
    vector <Disc>& choise;
};


#endif //TARGIL1_REVERSIGAMELOGIC_H