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

// Note: This data file does not adhere to an 80 column limit!

const std::string statStrings[NUMALLSTATS] = {
    "HP", "Atk", "Def", "SpA", "SpD", "Spe", "Acc", "Eva", "Crit"
};

const std::string statFullStrings[NUMALLSTATS] = {
    "HP", "Attack", "Defense", "Special Attack", "Special Defense", "Speed", "Accuracy", "Evasiveness", "Critical Hit Ratio"
};

const std::string typeStrings[MAXTYPES] = {
    "No Type", "Normal", "Grass", "Fire", "Water", "Electric", "Ice", "Bug",
    "Poison", "Fighting", "Flying", "Ground", "Rock", "Ghost", "Psychic",
    "Dragon", "Dark", "Steel", "Fairy", "Neutral", "Light"
};

const std::string natureStrings[NUMNATURES] = {
    "No Nature", "Hardy", "Lonely", "Brave", "Adamant", "Naughty", "Bold",
    "Docile", "Relaxed", "Impish", "Lax", "Timid", "Hasty", "Serious", "Jolly",
    "Naive", "Modest", "Mild", "Quiet", "Bashful", "Rash", "Calm", "Gentle",
    "Sassy", "Careful", "Quick"
};

const std::string itemStrings[NUMITEMS] = {
    "No Item", "Leftovers", "Choice Band", "Choice Scarf", "Choice Specs",
    "Light Ball", "Life Orb", "Light Clay", "King's Rock", "Focus Sash",
    "Black Sludge", "Oran Berry", "Sitrus Berry", "Eject Policy", "Red Card", "Eviolite",
    
    "Venusaurite", "Charizardite X", "Charizardite Y", "Blastoisinite", "Alakazite", "Gengarite", "Kangaskhanite", "Pinsirite", "Gyaradosite", "Aerodactylite", "Mewtwonite X", "Mewtwonite Y", "Ampharosite", "Scizorite", "Heracronite", "Houndoominite", "Tyranitarite", "Blazikenite", "Gardevoirite", "Mawilite", "Aggronite", "Medichamite", "Manectite", "Bannetite", "Absolite", "Garchompite", "Lucarionite", "Abomasite",
    
    "Swampertite", "Sceptilite", "Sableite", "Diancite", "Metagrossite", "Salamencite", "Altarite", "Slowbrite", "Audinite", "Lopunnite", "Latiasite", "Latiosite",
};

const std::string abilityStrings[NUMABILITIES] = {
    "No Ability", "Levitate", "Swift Swim", "Intimidate", "Huge Power",
    "Static", "Serene Grace", "Unaware", "Magic Bounce", "Pressure",
    "Sand Stream", "Multiscale", "Synchronize", "Clear Body", "Drizzle",
    "Drought", "Air Lock", "Stance Change", "Torrent", "Blaze", "Overgrow",
    "Swarm", "Technician", "Poison Point", "Snow Warning", "Anticipation",
    "Mold Breaker", "Pure Power", "Prankster", "Defiant", "Speed Boost", "Deathly Touch",
    "Skill Link", "Run Away", "Overcoat"
};

const std::string moveTypeStrings[NUMMOVETYPES] = {
    "Physical", "Special", "Status"
};

const std::string statusStrings[NUMSTATUSES] = {
    "OK", "PSN", "PSN", "PRZ", "BRN", "FRZ", "SLP", "FNT"
};

const std::string statusFullStrings[NUMSTATUSES] = {
    "Healthy", "Poisoned", "Badly Poisoned", "Paralyzed", "Burned", "Frozen",
    "Asleep", "Fainted"
};

const std::string statusFSNoun[NUMSTATUSES] = {
    "No Status", "Poison", "Toxic", "Paralyze", "Burn", "Freeze", "Sleep", "Faint"
};

const std::string statusStartStrings[NUMSTATUSES] = {
    "", "was poisoned!", "was badly poisoned!", "was paralyzed!", "was burned!", "was frozen solid!", "fell asleep!", "fainted!"
};

const std::string vstatusStrings[NUMVSTATUSES] = {
    "None", "Conf", "Attr", "Curs", "Blok", "Encr", "Trmt", "Taun", "Rmpg", "Prot", "Shld", "Fcus", "Flch", "Lfcs", "Subs", "Flyg", "Undr", "Dive", "Chrg",
    "Rchg", "Glow", "Razr", "Bash", "Phtm", "Shdw", "Bnce", "Geom", "Fshk",
    "Ibrn"
};

const std::string vstatusFullStrings[NUMVSTATUSES] = {
    "None", "Confused", "Attract", "Cursed", "Blocked", "Encore", "Torment",
    "Taunt", "Rampaging", "Protect", "Shield", "Focusing", "Flinch", "Lost Focus", "Substitute", "Flying", "Underground", "Diving", "Charging", "Recharging",
    "Glowing", "Razor Wind", "Skull Bash", "Phantom Force", "Shadow Force",
    "Bounce", "Geomancy", "Freeze Shock", "Ice Burn"
};

const std::string weatherStrings[NUMWEATHERS] = {
    "No Weather", "Sunny", "Rain", "Sandstorm", "Hail", "Fog", "Twilight", "Random"
};

const std::string weatherStartStrings[NUMWEATHERS] = {
    "", "The sunlight turned harsh.", "It started to rain.",
    "A sandstorm kicked up!", "It started to hail!", "Fog crept up thick as soup!", "The surroundings turned to twilight."
};

const std::string weatherEndStrings[NUMWEATHERS] = {
    "", "The sunlight faded.", "The rain stopped.", "The sandstorm subsided.",
    "The hail stopped.", "The fog lifted.", "Twilight ended."
};

const std::string weatherContStrings[NUMWEATHERS] = {
    "", "The sunlight is harsh.", "Rain continues to fall.",
    "The sandstorm rages on.", "Hail continues to fall.", "The fog is deep...", "The battlefield seems faint and dreamlike."
};

const std::string weatherHurtStrings[NUMWEATHERS] = {
    "", "", "", "is buffetted by the sandstorm!", "is pelted by the hail!"
};

const std::string genderStrings[4] = {
    "M", "F", "?", "-"
};

const std::string PKMNTRAINER = "PKMN Trainer";
const std::string YOUNGSTER = "Youngster";
const std::string GYMLEADER = "Gym Leader";
const std::string BUGCATCHER = "Bug Catcher";
const std::string LASS = "Lass";
const std::string ACETRAINER = "Ace Trainer";
const std::string ELITEFOUR = "Elite Four";
const std::string CHAMPION = "Champion";
const std::string HIKER = "Hiker";
const std::string SWIMMER = "Swimmer";

const std::string PSYTRAINER = "Psychic";
const std::string DRGNTAMER = "Dragon Tamer";
const std::string BIRDKEEPER = "Bird Keeper";
const std::string FAIRYTALE = "Fairy Tale Girl";
const std::string JUGGLER = "Juggler";
const std::string RICHBOY = "Rich Boy";
const std::string LADY = "Lady";
const std::string CUEBALL = "Cue Ball";
const std::string VETERAN = "Veteran";
const std::string SOCIALITE = "Socialite";

const std::string ROCKET = "Team Rocket Grunt";
const std::string CIPHER = "Cipher Peon";
const std::string FLARE = "Team Flare Admin";
const std::string BEAUTY = "Beauty";
const std::string POKEFAN = "Pokefan";
const std::string SAGETRAINER = "Sage";
const std::string ACTRESS = "Actress";
const std::string FISHERMAN = "Fisherman";

const std::string titleArray[NUMTITLES] = {
    PKMNTRAINER, YOUNGSTER, GYMLEADER, BUGCATCHER, LASS, ACETRAINER, ELITEFOUR,
    CHAMPION, HIKER, SWIMMER, PSYTRAINER, DRGNTAMER, BIRDKEEPER, FAIRYTALE,
    JUGGLER, RICHBOY, LADY, CUEBALL, VETERAN, SOCIALITE, ROCKET, CIPHER, FLARE,
    BEAUTY, POKEFAN, SAGETRAINER, ACTRESS, FISHERMAN
};

const std::string musicTracksStrings[NUMTRACKS] = {
    "None", "B&W Trainer Battle", "PBR Gateway Coliseum", "X&Y Trainer Battle", "RB&Y Trainer Battle", "RB&Y Elite Four", "RB&Y Champion", "RS&E Champion", "DPP&Pt Champion", "X&Y Champion", "RS&E Trainer Battle"
};

const std::string switchStringsA[2] = {
    "Off", "On"
};

const std::string switchStringsB[2] = {
    "Disabled", "Enabled"
};

const std::string switchStringsC[2] = {
    "No", "Yes"
};

const std::string switchStringsD[2] = {
    "False", "True"
};

const std::string locationStrings[NUMLOCATIONS] = {
    "No Location", "Coliseum", "Field", "Grass", "Beach", "Water", "River", "Ocean", "Cave", "Dark Cave", "Building", "Desert", "Mountain", "Volcano", "Snow", "Boreal", "Forest", "Jungle", "Industrial", "Bridge"
};

#endif /* defined(__PokemonThrowdown__strings__) */
