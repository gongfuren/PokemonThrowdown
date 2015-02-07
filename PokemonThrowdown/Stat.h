//
//  Stat.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Stat__
#define __PokemonThrowdown__Stat__

#include "Stats.h"

class Pokemon;

//
// Stat
// Represents a Pokemon stat during battle.
//
class Stat
{
public:
    Stat(Stats* stats);
    
    Stat(int amplitude, Stats* stats);
    
    Stat(int amplitude, int magnitude, Stats* stats);
    
    int getStatus() const;
    
    int getValue() const;
    
    int getEffectiveValue() const;
    
    virtual void raise(int amount);
    
    virtual void lower(int amount);
    
    virtual double getMultiplier() const;
    
    Pokemon* getPokemon() const;
    
    static const int MaxMagnitude = 6;
    
protected:
    int magnitude;
    int amplitude;
    
private:
    static constexpr double multipliers[MaxMagnitude * 2 + 1] = {
        0.25, 0.285, 0.3333, 0.40, 0.50, 0.6666, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0
    };
    Stats* stats;
};

#endif /* defined(__PokemonThrowdown__Stat__) */
