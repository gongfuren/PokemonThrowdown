//
//  mapdata.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__mapdata__
#define __pokemongame__mapdata__

#include "constants.h"

#include <string>
using namespace std;

struct mapdata
{
    string name;
};

const mapdata maplib[MAXTOTALMAPS] = {
    "Gateway Coliseum",
    "Sunset Coliseum",
    "Pokemon League",
    "Underground Coliseum"
};

#endif /* defined(__pokemongame__mapdata__) */
