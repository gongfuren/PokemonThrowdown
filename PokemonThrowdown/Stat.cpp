//
//  Stat.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Stat.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "Team.h"
#include "utilities.h" // println()
#include "Status.h"

constexpr double Stat::multipliers[MaxMagnitude * 2 + 1];

Stat::Stat(Stats* stats)
{
    magnitude = 0;
    amplitude = 100;
    this->stats = stats;
}

Stat::Stat(int amplitude, Stats* stats)
{
    this->magnitude = 0;
    this->amplitude = amplitude;
    this->stats = stats;
}

Stat::Stat(int amplitude, int magnitude, Stats* stats)
{
    this->amplitude = amplitude;
    this->magnitude = magnitude;
    this->stats = stats;
}

int Stat::getStatus() const
{
    return magnitude;
}

int Stat::getValue() const
{
    return amplitude;
}

int Stat::getEffectiveValue() const
{
    return amplitude * getMultiplier();
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

Pokemon* Stat::getPokemon() const
{
    return stats->getPokemon();
}