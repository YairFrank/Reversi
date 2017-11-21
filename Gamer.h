//
// Created by yair on 13/11/17.
//

//Yair Frank 203699566

#ifndef TARGIL1_GAMER_H
#define TARGIL1_GAMER_H
#include <string>
#include <vector>
#include "Disc.h"
#include "Board.h"
class Gamer {
public:;

    virtual int& getCount()=0;
    virtual char getName()=0;

protected:
    char name{};
    int count{};
};
#endif //TARGIL1_GAMER_H
