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

#define string std::string

class Team;

//
// Trainer
// Represents a Trainer in a battle.
//
class Trainer
{
public:
    enum Gender
    {
        Male = 0, Female
    };
    
    Trainer();
    
    ~Trainer();
    
    string getTitle() const;
    
    string getName() const;
    
    Team* getTeam() const;
    
    Gender getGender() const;
    
    string getTitleAndName() const;
    
private:
    string title;
    string name;
    Team* team;
    Gender gender;
};

#undef string

#endif /* defined(__PokemonThrowdown__Trainer__) */
