//
//  main.cpp
//  pokemongame
//
//  Created by Ian Cordero on 8/6/13.
//  Copyright (c) 2013-2014 Ian Cordero. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>
#include "constants.h"
#include "utilities.h"
#include "Battle.h"
#include "strings.h"
#include "settings.h"
using namespace std;

static void displayCredits();
static void titleScreen();

// Main

int main()
{
    // Title Screen
    titleScreen();
    
    // Initialize environment
    srand(static_cast<unsigned int>(time(NULL))); // RNG
    loadSettings(); // Settings
    
    bool ff = false;
    int choice, prog = 0;
    string opts[5];
    
    for (;;)
    {
        if (ff)
            titleScreen();
        else
            ff = true;
        
        // Main Menu
        opts[0] = "Play";
        opts[1] = "Trainers";
        opts[2] = "Settings";
        opts[3] = "Credits";
        opts[4] = "Quit";
        choice = selectorGadget(opts, 5, prog, 5, false);
        
        if (choice == 0) // Play
        {
            Battle b;
            b.start();
            cout << endl;
        }
        else if (choice == 1)
            customTrainers();
        else if (choice == 2)
            configureSettings();
        else if (choice == 3)
            displayCredits();
        else // Quit
            break;
    }
}

static void titleScreen()
{
    cout << "O***0***O***0***O***0" << endl
    << "* Pokemon Throwdown * v0.4.1" << endl
    << "0***O***0***O***0***O" << endl;
}

static void displayCredits()
{
    cout << "PokemonThrowdown" << endl;
    cout << "----------------" << endl;
    
    cout << "An originally-coded Pokemon simulator that is true to the game."
    << endl << endl
    
    << "All credit goes to Nintendo for original game design, "
    "mechanics, etc." << endl << endl << "Made by a huge fan."
    << endl << endl
    
    << "throwdown (n.) informal" << endl
    << "a performance by or competition between rappers, breakdancers, etc." << endl
    << "ex: a funky hip-hop throwdown." << endl << endl
    
    << "Pokemon \"Throwdown\" is a play on the popular web-based Pokemon Showdown battle simulator." << endl << endl
    
    << "(C) 2013-2014 Ian P. Cordero." << endl;
    // Contributors feel free to add your names here.
    
    confirmGadget();
}