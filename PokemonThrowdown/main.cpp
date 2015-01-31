//
//  main.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "utilities.h" // toInt()
#include <ctime> // time()
#include <cstdlib> // srand()
#include "Game.h" // Game

int main(int argc, const char* argv[])
{
    Game g;
    srand(toInt(time(NULL))); // Start RNG
    g.start();
}
