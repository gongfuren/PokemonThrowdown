//
//  Move.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include <iostream>
#include "Move.h"

using namespace std;

Move::Move()
{
    name = "Thunder Shock";
    power = 30;
    accuracy = 100;
    pP = 25;
    type = Special;
}

string Move::getName() const
{
    return name;
}

int Move::getPower() const
{
    return power;
}

int Move::getAccuracy() const
{
    return accuracy;
}

int Move::getPP() const
{
    return pP;
}