//
//  main.cpp
//  pokemongame
//
//  Created by Ian Cordero on 8/6/13.
//  Copyright (c) 2013-2014 Ian Cordero. All rights reserved.
//

#include <iostream>
#include <ctime> // time()
#include <unistd.h> // getopt()
#include <cstdlib> // srand()
#include "Game.h"
using namespace std;

// Command Line

bool savingEnabled = true;
static void commandLineParser(int argc, char* argv[]);

// Main //////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    // Command line arguments (if any)
    commandLineParser(argc, argv);
    
    // Initialize environment
    srand(static_cast<unsigned int>(time(NULL))); // RNG
    
    // Begin Game
    Game g;
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