//
//  HPStat.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "HPStat.h"
#include "Stat.h"
#include "exceptions.h"
#include "Pokemon.h" 
#include "Status.h"
#include "Trainer.h"
#include "Team.h" 
#include "utilities.h"
#include "Condition.h"

HPStat::HPStat(Stats* stats)
: Stat(200, 200, stats)
{
}

HPStat::HPStat(int amplitude, Stats* stats)
: Stat(amplitude, amplitude, stats)
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
    if (magnitude <= 0)
    {
        throw ZombiePokemonException();
    }
    
    if ((magnitude -= amount) <= 0)
    {
        magnitude = 0;
        
        getPokemon()->getStatus()->setCondition(new FaintCondition(getPokemon()));
        
        // TEMPORARY FIX (TODO)!!!
        println(getPokemon()->getTrainer()->getTitleAndName() + "'s " + getPokemon()->getFullName() + " fainted!");
        
        getPokemon()->getTrainer()->getTeam()->clearActive();
    }
}

double HPStat::getMultiplier() const
{
    throw HPMultiplierException();
}
