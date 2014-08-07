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

const int NUMTRAINERS = 12;

const trainerdata trainerlib[MAXTOTALTRAINERS] = {
    //                                      Pokemon
    // Name       Title        Male   Prize 1    2    3    4    5    6
    "Red",        PKMNTRAINER, true,  2900, 196, 143, 6,   9,   3,   25,
    "Steven",     CHAMPION,    true,  1000, 227, 306, 344, 346, 348, 376,
    "Blue",       PKMNTRAINER, true,  1200, 197, 65,  214, 59,  103, 248,
    "Ian",        ACETRAINER,  true,  7000, 468, 798, 637, 681, 788, 303,
    "Jean",       FAIRYTALE,   false, 3000, 382, 25,  286, 94,  157, 249,
    
    "Gabriel",    DRGNTAMER,   true,  5050, 65,  230, 121, 212, 248, 6,
    "Jessica",    HIKER,       false, 1100, 260, 429, 143, 242 ,448, 468,
    "Bill",       FISHERMAN,   true,  100,  129, 129, 129, 129, 129, 130,
    "Constance",  LADY,        false, 9000, 778, 794, 774, 797, 625, 786,
    "Lann",       JUGGLER,     true,  300,  787, 787, 787, 787, 787, 788,
    
    "Ariel",      SAGETRAINER, false, 6000, 789, 791, 793, 795, 797, -1,
    "Rhinne",     SAGETRAINER, false, 6000, 790, 792, 794, 796, 798, -1
};

#endif /* defined(__PokemonThrowdown__trainerdata__) */
