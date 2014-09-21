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

struct trainerdata
{
    std::string name;
    std::string title;
    bool male;
    int reward;
    int numPokemon;
};

const trainerdata trainerlib[NUMTRAINERS] = {
    // Name       Title        Male   Prize  NumPokemon
    "Red",        PKMNTRAINER, true,  7700,  6,
    "Green",      PKMNTRAINER, false, 8300,  6,
    "Blue",       PKMNTRAINER, true,  4000,  6,
    "Constance",  LADY,        false, 6500,  6,
    "Ian",        ACETRAINER,  true,  9900,  6,
    "Steven",     CHAMPION,    true,  5100,  6
};

#endif /* defined(__PokemonThrowdown__trainerdata__) */
