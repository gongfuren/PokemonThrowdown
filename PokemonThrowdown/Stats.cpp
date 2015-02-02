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

Stats::Stats()
{
    stats.push_back(new HPStat());
    stats.push_back(new Stat());
    stats.push_back(new Stat());
    stats.push_back(new Stat());
    stats.push_back(new Stat());
    stats.push_back(new Stat());
    stats.push_back(new BattleStat());
    stats.push_back(new BattleStat());
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