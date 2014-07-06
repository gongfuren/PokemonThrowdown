//
//  utils.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/6/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "constants.h"
#include <cstdlib>

// Auxiliary Function Implementations

// TODO: clean up these functions and their usage
void gyroscope(int& gyro, int& scope, Direction d)
{
    switch (d)
    {
        case Up:
            gyro = 0;
            scope = -1;
            break;
        case Right:
            gyro = 1;
            scope = 0;
            break;
        case Down:
            gyro = 0;
            scope = 1;
            break;
        case Left:
            gyro = -1;
            scope = 0;
            break;
        default:
            gyro = 0;
            scope = 0;
            break;
    }
}

double typeMultiplier(Type type1, Type type2)
{
    return typeArray[type1][type2];
}

double typeMultiplier(Type type1, Type type2, Type type3)
{
    if (type3 == NoType)
        return typeMultiplier(type1, type2);
    else
        return (typeMultiplier(type1, type2) * typeMultiplier(type1, type3));
}

int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    return lowest + (rand() % (highest - lowest + 1));
}

double natureMultiplier(Nature nature, int stat)
{
    return natureArray[nature][stat];
}
