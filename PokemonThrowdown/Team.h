//
//  Team.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Team__
#define __PokemonThrowdown__Team__

#include <iostream>

class Pokemon;

//
// Team
// Manages a Pokemon team.
//
class Team
{
public:
    static const int MaxNumPokemon = 6;
    
private:
    Pokemon* pokemon[MaxNumPokemon];
};

#endif /* defined(__PokemonThrowdown__Team__) */
