//
//  Ability.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/22/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Ability__
#define __PokemonThrowdown__Ability__

#include <iostream>
#include "abilitydata.h"

class Pokemon;

class Ability
{
public:
    Ability(int ID, Pokemon* pokemon);
    ~Ability();
    
    int getID() const;
    Pokemon* getPokemon() const;
    
private:
    int m_ID;
    std::string name;
    
    Pokemon* m_pokemon;
};

#endif /* defined(__PokemonThrowdown__Ability__) */
