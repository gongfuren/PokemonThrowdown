//
//  utilities.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "utilities.h"
#include <algorithm>

using namespace std;

int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    return lowest + (rand() % (highest - lowest + 1));
}

int randInt(int range)
{
    return randInt(0, range-1);
}

//
// flush()
// Clears std::cin.
//
static void flush()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getNumericalInput(int numChoices)
{
    int choice;
    
    for (;;)
    {
        print("?: ");
        
        cin >> choice;
        
        if (cin.fail() || choice < 1 || choice > numChoices)
        {
            flush();
            continue;
        }
        else
            break;
    }
    
    flush();
    return choice;
}

std::string getStringInput()
{
    string input;
    flush();
    print("?: ");
    getline(cin, input);
    return input;
}