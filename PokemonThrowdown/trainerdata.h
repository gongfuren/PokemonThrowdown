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

const int NUMTRAINERS = 10;

const trainerdata trainerlib[MAXTOTALTRAINERS] = {
    //                                      Pokemon
    // Name       Title        Male   Prize 1    2    3    4    5    6
    "Red",        PKMNTRAINER, true,  2900, 196, 25,  6,   9,   3,   143,
    "Steven",     CHAMPION,    true,  1000, 227, 306, 344, 346, 348, 376,
    "Blue",       PKMNTRAINER, true,  1200, 214, 65,  248, 59,  103, 197,
    "Ian",        ACETRAINER,  true,  7000, 373, 468, 637, 303, 720, 681,
    "Jean",       FAIRYTALE,   false, 3000, 25,  249, 382, 94,  157, 286,
    
    "Gabriel",    DRGNTAMER,   true,  5050, 6,   65,  121, 212, 248, 230,
    "Jessica",    HIKER,       false, 1100, 260, 429, 143, 242 ,448, 468,
    "Eric",       CUEBALL,     true,  100,  477, 330, 254, 242, 65,  157,
    "Constance",  LADY,        false, 9000, 786, 778, 774, 787, 625, 630,
    "Lann",       JUGGLER,     true,  3700, 764, 771, 150, 151, 707, 678
};

#endif /* defined(__PokemonThrowdown__trainerdata__) */
