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
#include <vector>

#define vector std::vector
#define string std::string

class Pokemon;

//
// Team
// Manages a Pokemon team.
//
class Team
{
public:
    Team();
    
    ~Team();
    
    vector<Pokemon*> getActive() const;
    
    vector<Pokemon*> getPokemon() const;
    
    vector<string> getPokemonNames() const;
    
    static const int FirstActiveSlot = 0;
    
private:
    vector<Pokemon*> active;
    vector<Pokemon*> pokemon;
};

#undef vector
#undef string

#endif /* defined(__PokemonThrowdown__Team__) */
