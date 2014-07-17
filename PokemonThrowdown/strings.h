//
//  strings.h
//  pokemongame
//
//  Created by Ian Cordero on 7/2/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__strings__
#define __PokemonThrowdown__strings__

#include "constants.h"

#include <string>
using namespace std;

// Note: This data file does not adhere to an 80 column limit!

const string statStrings[NUMALLSTATS] = {
    "HP", "Att", "Def", "SpA", "SpD", "Spe", "Acc", "Eva", "Crit"
};

const string statFullStrings[NUMALLSTATS] = {
    "HP", "Attack", "Defense", "Special Attack", "Special Defense", "Speed", "Accuracy", "Evasiveness", "Critical Hit Ratio"
};

const string typeStrings[MAXTYPES] = {
    "No Type", "Normal", "Grass", "Fire", "Water", "Electric", "Ice", "Bug",
    "Poison", "Fighting", "Flying", "Ground", "Rock", "Ghost", "Psychic",
    "Dragon", "Dark", "Steel", "Fairy", "Neutral", "Light"
};

const string natureStrings[NUMNATURES] = {
    "No Nature", "Hardy", "Lonely", "Brave", "Adamant", "Naughty", "Bold",
    "Docile", "Relaxed", "Impish", "Lax", "Timid", "Hasty", "Serious", "Jolly",
    "Naive", "Modest", "Mild", "Quiet", "Bashful", "Rash", "Calm", "Gentle",
    "Sassy", "Careful", "Quick"
};

const string itemStrings[NUMITEMS] = {
    "No Item", "Leftovers", "Choice Band", "Choice Scarf", "Choice Specs",
    "Light Ball", "Life Orb", "Light Clay", "King's Rock", "Focus Sash",
    "Black Sludge", "Oran Berry", "Sitrus Berry", "Eject Policy", "Red Card",
    
    "Venusaurite", "Charizardite X", "Charizardite Y", "Blastoisinite", "Alakazite", "Gengarite", "Kangaskhanite", "Pinsirite", "Gyaradosite", "Aerodactylite", "Mewtwonite X", "Mewtwonite Y", "Ampharosite", "Scizorite", "Heracronite", "Houndoominite", "Tyranitarite", "Blazikenite", "Gardevoirite", "Mawilite", "Aggronite", "Medichamite", "Manectite", "Bannetite", "Absolite", "Garchompite", "Lucarionite", "Abomasite",
    
    "Swampertite", "Sceptilite", "Sableite", "Diancite", "Latiasite", "Latiosite"
};

const string abilityStrings[NUMABILITIES] = {
    "No Ability", "Levitate", "Swift Swim", "Intimidate", "Huge Power",
    "Static", "Serene Grace", "Unaware", "MagicBounce", "Pressure",
    "Sand Stream", "Multiscale", "Synchronize", "Clear Body", "Drizzle",
    "Drought", "Air Lock", "Stance Change", "Torrent", "Blaze", "Overgrow",
    "Swarm", "Technician", "Poison Point", "Snow Warning", "Anticipation",
    "Mold Breaker", "Pure Power", "Prankster"
};

const string moveTypeStrings[NUMMOVETYPES] = {
    "Physical", "Special", "Status"
};

const string statusStrings[NUMSTATUSES] = {
    "OK", "PSN", "PSN", "PRZ", "BRN", "FRZ", "SLP", "FNT"
};

const string statusFullStrings[NUMSTATUSES] = {
    "Healthy", "Poisoned", "Badly Poisoned", "Paralyzed", "Burned", "Frozen",
    "Asleep", "Fainted"
};

const string statusFSNoun[NUMSTATUSES] = {
    "No Status", "Poison", "Toxic", "Paralyze", "Burn", "Freeze", "Sleep", "Faint"
};

const string statusStartStrings[NUMSTATUSES] = {
    "", "was poisoned!", "was badly poisoned!", "was paralyzed!", "was burned!", "was frozen solid!", "fell asleep!", "fainted!"
};

const string vstatusStrings[NUMVSTATUSES] = {
    "None", "Conf", "Attr", "Curs", "Blok", "Encr", "Trmt", "Taun", "Rmpg", "Prot", "Shld", "Fcus", "Flch", "Lfcs", "Subs"
};

const string vstatusFullStrings[NUMVSTATUSES] = {
    "None", "Confused", "Attract", "Cursed", "Blocked", "Encore", "Torment",
    "Taunt", "Rampaging", "Protect", "Shield", "Focusing", "Flinch", "Lost Focus", "Substitute"
};

const string weatherStrings[NUMWEATHERS] = {
    "No Weather", "Sunny", "Rain", "Sandstorm", "Hail"
};

const string weatherStartStrings[NUMWEATHERS] = {
    "", "The sunlight turned harsh.", "It started to rain.",
    "A sandstorm kicked up!", "It started to hail!"
};

const string weatherEndStrings[NUMWEATHERS] = {
    "", "The sunlight faded.", "The rain stopped.", "The sandstorm subsided.",
    "The hail stopped."
};

const string weatherContStrings[NUMWEATHERS] = {
    "", "The sunlight is harsh.", "Rain continues to fall.",
    "The sandstorm rages on.", "Hail continues to fall."
};

const string weatherHurtStrings[NUMWEATHERS] = {
    "", "", "", "is buffetted by the sandstorm!", "is pelted by the hail!"
};

const string genderStrings[4] = {
    "M", "F", "-", "?"
};

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
const string DRGNTAMER = "Dragon Tamer";
const string BIRDKEEPER = "Bird Keeper";
const string FAIRYTALE = "Fairy Tale Girl";
const string JUGGLER = "Juggler";

const string RICHBOY = "Rich Boy";
const string LADY = "Lady";
const string CUEBALL = "Cue Ball";
const string VETERAN = "Veteran";
const string SOCIALITE = "Socialite";

const string titleArray[NUMTITLES] = {
    PKMNTRAINER, YOUNGSTER, GYMLEADER, BUGCATCHER, LASS, ACETRAINER, ELITEFOUR,
    CHAMPION, HIKER, SWIMMER, PSYTRAINER, DRGNTAMER, BIRDKEEPER, FAIRYTALE,
    JUGGLER, RICHBOY, LADY, CUEBALL, VETERAN, SOCIALITE
};

#endif /* defined(__PokemonThrowdown__strings__) */
