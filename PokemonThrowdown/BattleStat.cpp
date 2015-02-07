//
//  BattleStat.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "BattleStat.h"
#include "Stat.h"

constexpr double BattleStat::battleMultipliers[MaxMagnitude * 2 + 1];

BattleStat::BattleStat(Stats* stats)
: Stat(1, 0, stats)
{
}

BattleStat::BattleStat(int amplitude, Stats* stats)
: Stat(amplitude, stats)
{
}

double BattleStat::getMultiplier() const
{
    return battleMultipliers[magnitude + MaxMagnitude];
}