//
//  Slot.h
//  pokemongame
//
//  Created by Ian Cordero on 6/7/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Slot__
#define __PokemonThrowdown__Slot__

#include <iostream>
#include "constants.h"
#include "Zone.h"

class Pokemon;
class Side;

class Slot : public Zone
// Represents a slot on one side of the battlefield
// Each Slot holds 0 or 1 Pokemon
{
public:
    Slot(Side* side, int X, int Y);
    ~Slot();
    
    // Return true if Pokemon in Slot exists and is not fainted
    bool isFull() const;
    
    Side* getSide() const;
    void weatherEffect(Weather weather);
    void fillSlot(Pokemon* pokemon);
    Pokemon* getPokemon() const;
    
private:
    Pokemon* m_pokemon;
    
    Side* m_side;
};

#endif /* defined(__PokemonThrowdown__Slot__) */
