//
//  Slot.h
//  pokemongame
//
//  Created by Ian Cordero on 6/7/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Slot__
#define __pokemongame__Slot__

#include <iostream>
#include "constants.h"

class Pokemon;
class Side;

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

class Slot
{
public:
    Slot(Side* side);
    ~Slot();
    
    Pokemon* getPokemon() const;
    
    Side* getSide() const;
    
    void weatherEffect(Weather weather);
    void fillSlot(Pokemon* pokemon);
    
private:
    Pokemon* m_pokemon;
    
    Side* m_side;
};

#endif /* defined(__pokemongame__Slot__) */
