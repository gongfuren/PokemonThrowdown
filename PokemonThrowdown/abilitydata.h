//
//  abilitydata.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/22/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__abilitydata__
#define __PokemonThrowdown__abilitydata__

#include <iostream>

#include "Event.h"
#include "strings.h"

// TODO: implement most abilities
enum PokeAbility
{
    PNoAbility, PLevitate, PSwiftSwim, PIntimidate, PHugePower, PStatic,
    PSereneGrace, PUnaware, PMagicBounce, PPressure, PSandStream, PMultiscale,
    PSynchronize, PClearBody, PDrizzle, PDrought, PAirLock, PStanceChange,
    PTorrent, PBlaze, POvergrow, PSwarm, PTechnician, PPoisonPoint,
    PSnowWarning, PAnticipation, PMoldBreaker, PPurePower, PPrankster,
    PDefiant
};

struct abilitydata
{
    int ID;
    int(Event::* reaction)(int);
};

const abilitydata abilitylib[100] = {
    PNoAbility, NULL,
    PIntimidate, &Event::Intimidate
};

#endif /* defined(__PokemonThrowdown__abilitydata__) */
