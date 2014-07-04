//
//  BattleData.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__BattleData__
#define __pokemongame__BattleData__

#include "constants.h"

struct BattleData
{
    int playerID;
    int opponentID;
    Weather weather;
};

const BattleData battlelib[MAXTOTALBATTLES] = {
    0, 1, NoWeather,
    0, 1, NoWeather,
};

#endif /* defined(__pokemongame__BattleData__) */
