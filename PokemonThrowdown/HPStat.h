//
//  HPStat.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__HPStat__
#define __PokemonThrowdown__HPStat__

#include "Stat.h"

#define override virtual

class HPStat : public Stat
{
public:
    HPStat(Stats* stats);
    
    HPStat(int amplitude, Stats* stats);
    
    override void raise(int amount);
    
    override void lower(int amount);
    
    override double getMultiplier() const;
};

#undef override

#endif /* defined(__PokemonThrowdown__HPStat__) */
