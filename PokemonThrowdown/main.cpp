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
#include "Battle.h"
#include "strings.h"
using namespace std;

// Options

// Main

int main()
{
    int choice;
    
    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(NULL)));
    
    for (;;)
    {
        // Title Screen
        cout << "O***0***O***0***O***0" << endl
        << "* Pokemon Throwdown * v0.2.2.3" << endl
        << "0***O***0***O***0***O" << endl;
        
        cout << "1: " << "New Game" << endl
        << "2: " << "Options" << endl
        << "3: " << "Credits" << endl
        << "4: " << "Quit" << endl;
        
        cin >> choice;
        
        if (choice == 1) // Play
        {
            Battle b;
            b.start();
            
            cout << endl;
        }
        else if (choice == 2) // Options (TODO)
        {
            cout << "Coming soon!" << endl;
        }
        else if (choice == 3) // Credits
        {
            cout << "PokemonThrowdown" << endl;
            cout << "----------------" << endl << endl;
            
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
            // Contributors feel free to add your names here
        }
        else // Quit
        {
            break;
        }
    }
}