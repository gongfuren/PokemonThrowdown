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

const trainerdata trainerlib[NUMTRAINERS] = {
    //                                      Pokemon
    // Name       Title        Male   Prize 1    2    3    4    5    6
    "Red",        PKMNTRAINER, true,  7700, 12,  13,  14,  15,  16,  17,
    "Green",      PKMNTRAINER, false, 8300, 0,   1,   2,   3,   4,   5,
    "Blue",       PKMNTRAINER, true,  4000, 18,  19,  20,  21,  22,  23,
    "Constance",  LADY,        false, 6500, 30,  31,  32,  33,  34,  35,
    "Ian",        ACETRAINER,  true,  9900, 6,   7,   8,   9,   10,  11,
    "Steven",     CHAMPION,    true,  5100, 24,  25,  26,  27,  28,  29
};

#endif /* defined(__PokemonThrowdown__trainerdata__) */
