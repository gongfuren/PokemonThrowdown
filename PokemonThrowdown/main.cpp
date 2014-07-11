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

// Main

int main()
{
    int choice;
    bool showFullHeader = true;
    
    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(NULL)));
    
    for (;;)
    {
        // Title Screen
        if (showFullHeader)
            cout << "O***0***O***0***O***0" << endl
            << "* Pokemon Throwdown *" << endl
            << "0***O***0***O***0***O" << endl;
        
        cout << "1: " << "Play" << endl
        << "2: " << "Options" << endl
        << "3: " << "Credits" << endl
        << "4: " << "Quit" << endl;
        
        cin >> choice;
        
        if (choice == 1) // Play
        {
            Battle b;
            b.start();
            showFullHeader = true;
            
            cout << endl;
        }
        else if (choice == 2) // Options (TODO)
        {
            cout << "Coming soon!" << endl;
            showFullHeader = false;
        }
        else if (choice == 3) // Credits
        {
            cout << "Pokemon Throwdown" << endl
            << "An originally-coded, Pokemon simulator that is true to the game. Made by a huge fan." << endl
            << "throwdown (n.) informal" << endl
            << "a performance by or competition between rappers, breakdancers, etc." << endl
            << "ex: a funky hip-hop throwdown." << endl;
            showFullHeader = false;
        }
        else // Quit
        {
            break;
        }
    }
}