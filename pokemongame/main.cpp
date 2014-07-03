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

void play();

// Main

int main()
{
    int choice;
    bool showFullHeader;
    
    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(NULL)));
    
    showFullHeader = true;
    
    for (;;)
    {
        // Title Screen
        if (showFullHeader)
            cout << bFStrings[0] << endl << bFStrings[1] << endl << bFStrings[2]
            << endl;
        
        cout << "1: " << bFStrings[3] << endl << "2: " << bFStrings[4] << endl
        << "3: " << bFStrings[5] << endl << "4: " << bFStrings[6] << endl;
        
        cin >> choice;
        
        if (choice == 1) // Play
        {
            Battle b;
            b.start();
            showFullHeader = true;
            
            cout << endl;
        }
        else if (choice == 2) // Options
        {
            cout << bFStrings[7] << endl;
        }
        else if (choice == 3) // Credits
        {
            cout << bFStrings[8] << endl << bFStrings[9] << endl
            << bFStrings[10] << endl << bFStrings[11] << endl << bFStrings[12]
            << endl << bFStrings[13] << endl << bFStrings[14] << endl;
        }
        else // Quit
        {
            break;
        }
        
        showFullHeader = false;
    }
}