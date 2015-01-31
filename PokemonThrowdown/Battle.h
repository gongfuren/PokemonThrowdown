//
//  Battle.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Battle__
#define __PokemonThrowdown__Battle__

#include <vector> 

class Trainer;
class Window;

//
// Battle
// Orchestrates Trainers and battle phases.
//
class Battle
{
public:
    Battle(Window* window);
    
    void start();
    
private:
    std::vector<Trainer*> trainers;
    Window* window;
};

#endif /* defined(__PokemonThrowdown__Battle__) */
