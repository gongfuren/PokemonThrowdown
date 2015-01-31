//
//  Stat.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Stat.h"
#include "exceptions.h"

constexpr double Stat::multipliers[Stats::MaxNumStats * 2 + 1];

constexpr double BattleStat::battleMultipliers[Stats::MaxNumStats * 2 + 1];

Stat::Stat(int amplitude)
{
    this->magnitude = 0;
    this->amplitude = amplitude;
}

Stat::Stat(int amplitude, int magnitude)
{
    this->amplitude = amplitude;
    this->magnitude = magnitude;
}

int Stat::getStatus() const
{
    return magnitude;
}

int Stat::getValue() const
{
    return amplitude;
}

void Stat::raise(int amount)
{
    if ((magnitude += amount) > MaxMagnitude)
    {
        magnitude = MaxMagnitude;
    }
}

void Stat::lower(int amount)
{
    if ((magnitude -= amount) < -MaxMagnitude)
    {
        magnitude = -MaxMagnitude;
    }
}

double Stat::getMultiplier() const
{
    return multipliers[magnitude + MaxMagnitude];
}

HPStat::HPStat(int amplitude)
: Stat(amplitude, amplitude)
{
}

void HPStat::raise(int amount)
{
    if ((magnitude += amount) > amplitude)
    {
        magnitude = amplitude;
    }
}

void HPStat::lower(int amount)
{
    if ((magnitude -= amount) < 0)
    {
        magnitude = 0;
    }
}

double HPStat::getMultiplier() const
{
    throw HPMultiplierException();
}

double BattleStat::getMultiplier() const
{
    return battleMultipliers[magnitude + MaxMagnitude];
}