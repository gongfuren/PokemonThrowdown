//
//  MapData.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__MapData__
#define __pokemongame__MapData__

#include "constants.h"

#include <string>
using namespace std;

struct MapData
{
    string name;
};

const MapData maplib[MAXTOTALMAPS] = {
    "Gateway Coliseum",
    "Sunset Coliseum",
    "Pokemon League",
    "Underground Coliseum"
};

#endif /* defined(__pokemongame__MapData__) */
