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
    PKMNTRAINER, YOUNGSTER, GYMLEADER, BUGCATCHER, LASS, ACETRAINER, ELITEFOUR, CHAMPION, HIKER, SWIMMER, PSYTRAINER
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
    "Blue",       CHAMPION,    true,  1000, 214, 65,  248, 59,  103,  9,
    "Ian",        PKMNTRAINER, true,  1000, 721, 149, 248, 303, 720, 681,
    "Beth",       PSYTRAINER,  false, 200,  -1,  -1,  -1,  -1,  -1,  -1,
    
    "Max",        BUGCATCHER,  true,  200,  -1,  -1,  -1,  -1,  -1,  -1,
    "Joey",       YOUNGSTER,   true,  200,  -1,  -1,  -1,  -1,  -1,  -1,
    "Dana",       LASS,        false, 200,  -1,  -1,  -1,  -1,  -1,  -1,
    "Brock",      GYMLEADER,   true,  500,  -1,  -1,  -1,  -1,  -1,  -1,
    "Misty",      GYMLEADER,   false, 500,  -1,  -1,  -1,  -1,  -1,  -1,
    
    "Samuel",     HIKER,       true,  400,  -1,  -1,  -1,  -1,  -1,  -1,
    "Michael",    SWIMMER,     true,  350,  -1,  -1,  -1,  -1,  -1,  -1,
    "Robert",     ACETRAINER,  true,  900,  -1,  -1,  -1,  -1,  -1,  -1,
    "Ariel",      ACETRAINER,  false, 900,  -1,  -1,  -1,  -1,  -1,  -1,
    "Rex",        PKMNTRAINER, true,  1000, -1,  -1,  -1,  -1,  -1,  -1,
    
    "Solomon",    PKMNTRAINER, true,  1000, -1,  -1,  -1,  -1,  -1,  -1
};

#endif /* defined(__pokemongame__TrainerData__) */
