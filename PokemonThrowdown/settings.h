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
using namespace std;

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

// Variables set within run of the program. Plan to have the option to save
// settings to a file and access them in a future run of the program.

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

// Line number references for the settings file

const uint8_t NAMETAG = 0;
const uint8_t WEATHERTAG = 1;
const uint8_t TRAINERSTART = 2;
const int TRAINERENTRYSIZE = 4;
const int POKEENTRYSIZE = 8;
const int TNPENTRY = TRAINERENTRYSIZE + POKEENTRYSIZE * 6;

// String constants for settings file

const string SETTINGSTAG = "PKTDS04IPC2014___";
const string SETTINGSFILENAME = "PKTDSettings.txt";
const string EXPORTFILENAME = "PKTDExport";

#endif /* defined(__PokemonThrowdown__settings__) */
