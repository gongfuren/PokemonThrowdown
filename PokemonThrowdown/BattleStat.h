//
//  BattleStat.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__BattleStat__
#define __PokemonThrowdown__BattleStat__

#include "Stat.h"

#define override virtual

class Stats;

class BattleStat : public Stat
{
public:
    BattleStat(Stats* stats);
    
    BattleStat(int amplitude, Stats* stats);
    
    override double getMultiplier() const;
    
private:
    static constexpr double battleMultipliers[MaxMagnitude * 2 + 1] = {
        0.3333, 0.38, 0.43, 0.5, 0.6, 0.75, 1.00, 1.3333, 1.6666, 2.0, 2.3333,
        2.6666, 3.0
    };
};

#undef override

#endif /* defined(__PokemonThrowdown__BattleStat__) */
