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

// Settings Functions

// settings()
// Allow user to configure settings to fit their needs.
void settings();

// Settings Variables
// Variables set within run of the program. Plan to have the option to save
// settings to a file and access them in a future run of the program.

extern int musicID;
extern int weatherID;
extern bool soundEffects;
extern bool animations;

#endif /* defined(__PokemonThrowdown__settings__) */
