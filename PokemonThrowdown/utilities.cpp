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
