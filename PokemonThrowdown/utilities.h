//
//  utilities.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/29/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__util__
#define __PokemonThrowdown__util__

#include <iostream>
#include "constants.h"

// Auxiliary Function Declarations ///////////////////////////////////////////

// randInt()
// Returns a randomly chosen integer between lowest and highest inclusive
int randInt(int lowest, int highest);

// typeMultiplier()
// Returns multiplier corresponding to 'type1's damage on 'type2' or
// 'type2'/'type3'
//
// Ex: typeMultiplier(DragonType, FairyType) == 0.0
double typeMultiplier(Type type1, Type type2, Type type3 = NoType);

// natureMultiplier()
// Returns multiplier corresponding to nature's influence on stat
//
// Ex: natureMultiplier(AdamantNature, AttStat) == 1.1
double natureMultiplier(Nature nature, int stat);

// selectorGadget()
//
// Organizes and displays all 'sizeo' indices of opts[] as a user-interactive
// menu.
//
// Returns index of opts[] corresponding to user choice. If user chooses "Back"
// (Back is enabled by default) returns -1. You must check and do something useful
// with this value (i.e. break out of a loop).
//
// Allows pagination, with 'entriesPerPage' choices per page, not including
// extra items.
//
// Starts at index 'prog' (and updates it so you can call this function again and
// not lose your place).
//
// Pass in specialOpts[] for extra options on every page. specialEndOpts[] for
// options only at the end of the list after opts[], specialBeginOpts[] for
// options only at the beginning.
int selectorGadget(std::string opts[], int sizeo, int& prog,
                   int entriesPerPage = 10, bool back = true,
                   std::string specialOpts[] = NULL, int sizes = 0,
                   std::string specialBeginOpts[] = NULL, int sizeb = 0,
                   std::string specialEndOpts[] = NULL, int sizee = 0);

// inputGadget()
// Simple utility for accepting a checked int input from the command line.
int inputGadget(int numChoices);

// numericalGadget()
// Accepts input from cin between min and max, inclusive
int numericalGadget(int min, int max, string error = "Invalid input!");

// confirmGadget()
// Displays an OK prompt for the user at the command line
void confirmGadget();

// stringToNumber()
// Simple conversion to int from a string
int stringToNumber(const string& string);

#endif /* defined(__PokemonThrowdown__util__) */
