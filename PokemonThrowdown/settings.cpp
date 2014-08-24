//
//  settings.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 8/23/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "settings.h"
#include "utilities.h"
#include "constants.h"
#include "strings.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

// Default settings values
int musicID = NoMusic;
int weatherID = RandomWeather;
bool soundEffects = false;
bool animations = false;

bool customTrainers();

void settings()
{
    int choice = -1, prog = 0;
    const int numSettings = 2;
    string opts[numSettings];
    
    while (1)
    {
        cout << "Configure Settings" << endl;
        
        {
            ostringstream tmp;
            tmp << "Start Weather: " << weatherStrings[weatherID];
            opts[0] = tmp.str();
        }
        
        opts[1] = "Custom Trainers";
        
        choice = selectorGadget(opts, numSettings-1, prog);
        
        switch (choice)
        {
            case 0:
                weatherID = (weatherID+1) % NUMWEATHERS;
            case 1:
                if (customTrainers())
                    return;
                break;
            default:
                return;
        }
    }
}

bool customTrainers()
{
    return false;
}