//
// Created by yair on 25/10/17.
//

//Yair Frank 203699566

#ifndef TARGIL1_BOARD_H
#define TARGIL1_BOARD_H


#include "Disc.h"
#include "Player.h"


class Board {
public:
    /**
     * Constructor
     * @param size
     */
    Board (int size);
    /**
     * Building the matrix, using the value of size
     */
    void buildMatrix();
    /**
     * Filling the matrix with spaces, including the chars in the center
     */
    void fillMatrix();
    /**
     * Printing the matrix
     */
    void print() const;
    Disc** getBoard();
    void putDisk(char disk , int row, int column);
    /**
     * Destructor
     */
    ~Board();
private:
    int size;
    Disc** matrix;
};


#endif //TARGIL1_BOARD_H
