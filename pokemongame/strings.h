//
//  strings.h
//  pokemongame
//
//  Created by Ian Cordero on 7/2/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__strings__
#define __pokemongame__strings__

#include "constants.h"

#include <iostream>
#include <string>
using namespace std;

// Note: This data file does not adhere to an 80 column limit!

// Battle Flow Strings
const string bFStrings[200] = {
    "O***0***O***0***O***0", // 0
    "* Pokemon Throwdown *",
    "0***O***0***O***0***O",
    "Play",
    "Options",
    "Credits", // 5
    "Quit",
    "Coming soon!",
    "Pokemon Throwdown",
    "An originally-coded, Pokemon simulator that is true to the game. Made by a huge fan.",
    "throwdown (n.) informal", // 10
    "a performance by or competition between rappers, breakdancers, etc.",
    "ex: a funky hip-hop throwdown.",
    "",
    "Pokemon \"Throwdown\" is a play on the popular web-based Pokemon Showdown battle simulator.",
    "Choose lead Pokemon", // 15
    "Choose",
    "a trainer",
    "an opponent",
    "You chose",
    "Confirm", // 20
    "Pokemon", // 21
    "Cancel", // 22
    "Summary",
    "Check Moves",
    "Item", // 25
    "Ability",
    "Base Stats",
    "Lv", // 28
    "Type",
    "Damage", // 30
    "Accuracy", // 31
    "Attack", // 32
    "Move", // 33
    "would like to battle!",
    "is tightening its focus!", // 35
    "became confused due to fatigue!",
    "Turn",
    "is hurt by its burn!",
    "is hurt by poison!",
    "went to sleep!", // 40
    "HP was restored!",
    "HP can't go any higher!",
    "It doesn't affect",
    "A critical hit!",
    "It's super effective!", // 45
    "It's not very effective...",
    "It's a one-hit KO!",
    "Nature",
    "The match was a draw!",
    "won the battle!", // 50
    "Got",
    "for winning!",
    "What would you like to do?",
    "Fight!",
    "Bag", // 55
    "Run",
    "Are you sure you'd like to run and forfeit the match?",
    "Yes",
    "No",
    "has forfeited the match.", // 60
    "Choose a Pokemon",
    "In Battle",
    "What to do with",
    "Switch",
    "is fainted and cannot battle.", // 65
    "is already out!",
    "Select a move",
    "*Mega Evolution*",
    "Selected",
    "Move Info", // 70
    "sent out",
    "withdrew",
    "You can't do that right now.",
    "is exerting its Pressure!",
    "protected itself!", // 75
    "avoided the attack!",
    "was not lowered!",
    "can't go any lower!",
    "fell!",
    "was minimized!", // 80
    "harshly fell!",
    "fell dramatically!",
    "can't go any higher!",
    "can't go any higher!",
    "maximized its", // 85
    "increased!",
    "sharply increased!",
    "drastically increased!",
    "is paralyzed! It can't move!",
    "is fast asleep.", // 90
    "woke up!",
    "is frozen solid!",
    "thawed out!",
    "flinched!",
    "lost its focus and couldn't move!", // 95
    "snapped out of its confusion!",
    "is confused!",
    "hurt itself in its confusion!",
    "is reacting to",
    "Mega Ring!", // 100
    "has Mega Evolved into Mega",
    "Changed to",
    "Forme!",
    "used",
    "But it failed!", // 105
    "But there was no target!",
    "Blade",
    "Shield"
};

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
    
    "Latiasite", "Latiosite"
};

const string abilityStrings[NUMABILITIES] = {
    "No Ability", "Levitate", "Swift Swim", "Intimidate", "Huge Power",
    "Static", "Serene Grace", "Unaware", "MagicBounce", "Pressure",
    "Sand Stream", "Multiscale", "Synchronize", "Clear Body", "Drizzle",
    "Drought", "Air Lock", "Stance Change", "Torrent", "Blaze", "Overgrow",
    "Swarm", "Technician", "Poison Point", "Snow Warning", "Anticipation",
    "Mold Breaker", "Pure Power"
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

#endif /* defined(__pokemongame__strings__) */
