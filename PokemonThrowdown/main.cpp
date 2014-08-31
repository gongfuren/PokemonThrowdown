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
#include <unistd.h>
#include <cstdlib>
#include "constants.h"
#include "utilities.h"
#include "Battle.h"
#include "strings.h"
#include "settings.h"
using namespace std;

// CL Option Vars

bool savingEnabled = true;

// Helper Function Declarations

static void commandLineParser(int argc, char* argv[]);
static void usage(char* argn);
static void titleScreen();
static void startBattle();
static void displayCredits();
static void displayHelp(char* argn);

// Main //////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    bool reflashTitle = false, rerun = true;
    int prog = 0;
    const int numOpts = 6;
    string opts[numOpts] = { "Play", "Trainers", "Settings", "Credits", "Help", "Quit" };
    
    // Command line arguments (if any)
    commandLineParser(argc, argv);
    
    // Title Banner
    titleScreen();
    
    // Initialize environment
    srand(static_cast<unsigned int>(time(NULL))); // RNG
    loadSettings(); // Settings
    
    while (rerun)
    {
        // Title Screen
        if (reflashTitle)
            titleScreen();
        else
            reflashTitle = !reflashTitle;
        
        switch (selectorGadget(opts, numOpts, prog, numOpts, false))
        {
            case 0:
                startBattle();
                break;
            case 1:
                customTrainers();
                break;
            case 2:
                configureSettings();
                break;
            case 3:
                displayCredits();
                break;
            case 4:
                displayHelp(argv[0]);
                break;
            default:
                rerun = false;
        }
    }
}

// Helper Functions //////////////////////////////////////////////////////////

static void titleScreen()
{
    cout << "O***0***O***0***O***0" << endl
    << "* Pokemon Throwdown * " << VERSIONNUMBER << endl
    << "0***O***0***O***0***O" << endl;
}

static void startBattle()
{
    Battle b;
    b.start();
}

static void displayCredits()
{
    cout << "PokemonThrowdown:" << endl;
    
    cout << "An originally-coded Pokemon simulator that is true to the game." << endl
    
    << "All credit goes to Nintendo for original game design, mechanics, etc." << endl
    
    << "Made by a huge fan." << endl;
    
    confirmGadget();
    
    cout << "throwdown (n.) informal" << endl
    << "a performance by or competition between rappers, breakdancers, etc." << endl
    << "ex: a funky hip-hop throwdown." << endl;
    
    cout << "Pokemon \"Throwdown\" is a play on the popular web-based Pokemon Showdown battle simulator." << endl
    
    << "(C) 2013-2014 Ian P. Cordero." << endl;
    // Contributors feel free to add your names here.
    
    confirmGadget();
}

static void displayHelp(char* argn)
{
    cerr << "Pokemon Throwdown Command Line Interface" << endl;
    
    usage(argn);
    
    confirmGadget();
    
    cerr << "Options Breakdown:" << endl
    << "-d\n\tDisable save file capability (team export will still be available)." << endl;
    
    confirmGadget();
}

// Command Line //////////////////////////////////////////////////////////////

static void usage(char* argn)
{
    cerr << "Usage: " << argn << " [-d]" << endl;
}

static void commandLineParser(int argc, char* argv[])
{
    for (;;)
    {
        switch (getopt(argc, argv, "d"))
        {
            case 'd':
                savingEnabled = false;
                break;
            default:
                usage(argv[0]);
                exit(1);
            case -1:
                goto options_exhausted___;
        }
    }
options_exhausted___:
    ;
}