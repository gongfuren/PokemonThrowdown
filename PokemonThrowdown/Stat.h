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

//
// Stat
// Represents a Pokemon stat during battle.
//
class Stat
{
public:
    Stat(int amplitude);
    
    Stat(int amplitude, int magnitude);
    
    int getStatus() const;
    
    int getValue() const;
    
    virtual void raise(int amount);
    
    virtual void lower(int amount);
    
    virtual double getMultiplier() const;
    
    static const int MaxMagnitude = 6;
    
protected:
    int magnitude;
    int amplitude;
    
private:
    static constexpr double multipliers[Stats::MaxNumStats * 2 + 1] = {
        0.25, 0.285, 0.3333, 0.40, 0.50, 0.6666, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0
    };
};

#define override virtual

class HPStat : public Stat
{
public:
    HPStat(int amplitude);
    
    override void raise(int amount);
    
    override void lower(int amount);
    
    override double getMultiplier() const;
};

class BattleStat : public Stat
{
public:
    override double getMultiplier() const;
    
private:
    static constexpr double battleMultipliers[Stats::MaxNumStats * 2 + 1] = {
        0.3333, 0.38, 0.43, 0.5, 0.6, 0.75, 1.00, 1.3333, 1.6666, 2.0, 2.3333,
        2.6666, 3.0
    };
};

#undef override

#endif /* defined(__PokemonThrowdown__Stat__) */
