//
//  Trainer.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Trainer__
#define __PokemonThrowdown__Trainer__

#include <iostream>

class Team;

//
// Trainer
// Represents a Trainer in a battle.
//
class Trainer
{
public:
    
private:
    std::string title;
    std::string name;
    Team* team;
    enum Gender { Male = 0, Female } gender;
};

#endif /* defined(__PokemonThrowdown__Trainer__) */
