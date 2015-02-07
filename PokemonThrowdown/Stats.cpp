//
//  Stats.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include <vector>
#include "Stats.h"
#include "Stat.h"
#include "HPStat.h" 
#include "BattleStat.h"

Stats::Stats(Pokemon* pokemon)
{
    stats.push_back(new HPStat(this));
    stats.push_back(new Stat(this));
    stats.push_back(new Stat(this));
    stats.push_back(new Stat(this));
    stats.push_back(new Stat(this));
    stats.push_back(new Stat(this));
    stats.push_back(new BattleStat(this));
    stats.push_back(new BattleStat(this));
    this->pokemon = pokemon;
}

Stats::~Stats()
{
    for (Stat* stat : stats)
    {
        delete stat;
    }
}

Stat* Stats::getHP() const
{
    return stats[HP];
}

Stat* Stats::getAtt() const
{
    return stats[Att];
}

Stat* Stats::getDef() const
{
    return stats[Def];
}

Stat* Stats::getSpA() const
{
    return stats[SpA];
}

Stat* Stats::getSpD() const
{
    return stats[SpD];
}

Stat* Stats::getSpe() const
{
    return stats[Spe];
}

Stat* Stats::getAcc() const
{
    return stats[Acc];
}

Stat* Stats::getEva() const
{
    return stats[Eva];
}

Pokemon* Stats::getPokemon() const
{
    return pokemon;
}