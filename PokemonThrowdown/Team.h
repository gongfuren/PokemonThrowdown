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
class Trainer;
class Slot;

//
// Team
// Manages a Pokemon team.
//
class Team
{
public:
    Team(Trainer* trainer);
    
    ~Team();
    
    Slot* getSlot() const;
    
    vector<Slot*> getSlots() const;
    
    vector<Pokemon*> getPokemon() const;
    
    vector<string> getPokemonNames() const;
    
    vector<string> getPokemonNamesWithStatus() const;
    
    void setActive(Pokemon* pokemon);
    
    void clearActive();
    
    Trainer* getTrainer() const;
    
    static const int FirstSlot = 0;
    static const int FirstPokemon = 0;
    
private:
    vector<Slot*> slots;
    vector<Pokemon*> pokemon;
    Trainer* trainer;
};

#undef vector
#undef string

#endif /* defined(__PokemonThrowdown__Team__) */
