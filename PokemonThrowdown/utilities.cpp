//
//  utilities.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "utilities.h"

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
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getNumericalInput(int numChoices)
{
    int choice;
    
    for (;;)
    {
        print("?: ");
        
        std::cin >> choice;
        
        if (std::cin.fail() || choice < 1 || choice > numChoices)
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
    std::string input;
    flush();
    print("?: ");
    getline(std::cin, input);
    return input;
}