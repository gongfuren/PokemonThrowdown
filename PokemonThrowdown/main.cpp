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

// Main

int main()
{
    int choice, prog = 0;
    string opts[4], confirm[1];
    
    // Initialize environment
        // Random number generator
    srand(static_cast<unsigned int>(time(NULL)));
    
    for (;;)
    {
        // Title Screen
        cout << "O***0***O***0***O***0" << endl
        << "* Pokemon Throwdown * v0.3" << endl
        << "0***O***0***O***0***O" << endl;
        
        opts[0] = "Play";
        opts[1] = "Settings";
        opts[2] = "Credits";
        opts[3] = "Quit";
        
        choice = selectorGadget(opts, 4, prog, 4, false);
        
        if (choice == 0) // Play
        {
            Battle b;
            b.start();
            
            cout << endl;
        }
        else if (choice == 1) // Options (TODO)
            settings();
        else if (choice == 2) // Credits
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
            
            confirm[0] = "OK";
            
            choice = selectorGadget(confirm, 1, prog, 1, false);
        }
        else // Quit
            break;
    }
}

void options()
{
    
}