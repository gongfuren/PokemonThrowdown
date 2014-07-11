//
//  TrainerData.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__TrainerData__
#define __pokemongame__TrainerData__

#include "constants.h"

#include <string>
using namespace std;

const string PKMNTRAINER = "PKMN Trainer";
const string YOUNGSTER = "Youngster";
const string GYMLEADER = "Gym Leader";
const string BUGCATCHER = "Bug Catcher";
const string LASS = "Lass";
const string ACETRAINER = "Ace Trainer";
const string ELITEFOUR = "Elite Four";
const string CHAMPION = "Champion";
const string HIKER = "Hiker";
const string SWIMMER = "Swimmer";
const string PSYTRAINER = "Psychic";

const int NUMTITLES = 11;

const string titleArray[NUMTITLES] = {
    PKMNTRAINER, YOUNGSTER, GYMLEADER, BUGCATCHER, LASS, ACETRAINER, ELITEFOUR,
    CHAMPION, HIKER, SWIMMER, PSYTRAINER
};

struct TrainerData
{
    string name;
    string title;
    bool male;
    int reward;
    int pokemonIDs[MAXPOKEMON];
};

const int NUMTRAINERS = 4;

const TrainerData trainerlib[MAXTOTALTRAINERS] = {
    //                                      Pokemon
    // Name       Title        Male   Prize 1    2    3    4    5    6
    "Red",        PKMNTRAINER, true,  1000, 196, 25,  6,   9,   3,   143,
    "Steven",     CHAMPION,    true,  1000, 227, 306, 344, 346, 348, 376,
    "Blue",       CHAMPION,    true,  1000, 214, 65,  248, 59,  103,  197,
    "Ian",        ACETRAINER,   true,  1000, 774, 721, 637, 303, 720, 681,
    "KC",         PKMNTRAINER, false, 1000, 25,  249, 382,  94,  157,  286,

    "Anjo",       PKMNTRAINER, true,  1000,  6,  65,  121,  212,  248,  230,
    "Jessica",    ACETRAINER,  false, 1000, 260, 429, 143, 242 ,448, 468,
    "Erick",      PSYTRAINER,  true,  1000, 477, 330, 254, 242, 65,  157,
    "Steven",     PSYTRAINER,  true,  1000, 65,  376, 386, 385, 197,  150
};

#endif /* defined(__pokemongame__TrainerData__) */
