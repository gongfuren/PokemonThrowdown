//
//  Stats.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Stats.h"
#include "Stat.h"

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