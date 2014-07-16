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

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

class Slot : public Zone
// Represents a slot on one side of the battlefield
// Each Slot holds 0 or 1 Pokemon
{
public:
    Slot(Side* side);
    ~Slot();
    
    // Return true if Pokemon in Slot exists and is alive
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
