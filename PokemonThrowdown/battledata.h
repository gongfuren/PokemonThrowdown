//
//  battledata.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__battledata__
#define __pokemongame__battledata__

#include "constants.h"

struct battledata
{
    int playerID;
    int opponentID;
    Weather weather;
};

const battledata battlelib[MAXTOTALBATTLES] = {
    0, 1, NoWeather,
    0, 1, NoWeather,
};

#endif /* defined(__pokemongame__battledata__) */
