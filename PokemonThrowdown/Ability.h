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
#include "Reactor.h"

class Pokemon;

// Vastly unfinished

class Ability : public Reactor
{
public:
    // Other
    void flash() const;
    
    // Accessor Functions
    std::string getName() const;
    int getID() const;
    Pokemon* getPokemon() const;
    
    // Construction and Destruction
    Ability(int ID, Pokemon* pokemon);
    ~Ability();
    
private:
    int m_ID;
    std::string m_name;
    
    Pokemon* m_pokemon;
};

#endif /* defined(__PokemonThrowdown__Ability__) */
