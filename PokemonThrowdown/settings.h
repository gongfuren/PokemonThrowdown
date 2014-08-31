//
//  settings.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 8/23/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__settings__
#define __PokemonThrowdown__settings__

#include <iostream>
#include "constants.h"

struct trainerdata;
struct pokedynamicdata;

// Settings Functions ////////////////////////////////////////////////////////

// configureSettings()
// Allow user to configure settings to fit their needs.
void configureSettings();

// customTrainers()
// Allow user to edit custom trainers.
bool customTrainers();

// loadSettings()
// Load settings from settings file.
// Called automatically upon program start.
bool loadSettings();

// chosePokemon()
// Allow user to view summary of Pokemon and moves.
bool chosePokemon(int index, bool confirm = true);
bool choseMove(int index, bool confirm = true);

// Settings Variables ////////////////////////////////////////////////////////

// At the command line

extern bool savingEnabled;

// Within the program

extern int musicID;
extern int weatherID;
extern bool soundEffects;
extern bool animations;
extern int volumeLevel;
extern bool muteVolume;
extern int locationID;
extern int numCustomTrainers;
extern int numCustomPokemon[MAXCTRAINERS];

extern pokedynamicdata pokedynamicarray[MAXCTRAINERS][MAXPOKEMON];
extern trainerdata trainerarray[MAXCTRAINERS];

extern const pokedynamicdata* pokebattlers[MAXPOKEMON];

extern int numExports;

// Line number references

const int NAMETAG = 0;
const int WEATHERTAG = 1;
const int TRAINERSTART = 2;
const int TRAINERENTRYSIZE = 4;
const int POKEENTRYSIZE = 8;
const int TNPENTRY = TRAINERENTRYSIZE + POKEENTRYSIZE * 6;

// String constants for settings file

const std::string SETTINGSTAG = "PKTDS04IPC2014___";
const std::string SETTINGSFILENAME = "PKTDSettings.txt";
const std::string EXPORTFILENAME = "PKTDExport";

const std::string VERSIONNUMBER = "v0.4.3";

#endif /* defined(__PokemonThrowdown__settings__) */
