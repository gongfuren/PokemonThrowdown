//
//  trainerdata.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__trainerdata__
#define __PokemonThrowdown__trainerdata__

#include "constants.h"
#include "strings.h"

#include <string>
using namespace std;

struct trainerdata
{
    string name;
    string title;
    bool male;
    int reward;
    int pokemonIDs[MAXPOKEMON];
};

const int NUMTRAINERS = 2;

const trainerdata trainerlib[MAXTOTALTRAINERS] = {
    //                                      Pokemon
    // Name       Title        Male   Prize 1    2    3    4    5    6
    "Red",        PKMNTRAINER, true,  7700, 6,   7,   8,   9,   10,  11,
    "Ian",        ACETRAINER,  true,  7000, 0,   1,   2,   3,   4,   5,
    "Blue",       PKMNTRAINER, true,  1200, 12,  13,  14,  15,  16,  17,
    "Steven",     CHAMPION,    true,  1900, 18,  19,  20,  21,  22,  23,
};

#endif /* defined(__PokemonThrowdown__trainerdata__) */
