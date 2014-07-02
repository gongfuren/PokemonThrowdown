//
//  Computer.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/15/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Computer.h"
#include "Pokemon.h"

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

Computer::Computer(TrainerData h, Battle* battle)
: Trainer(h, battle)
{
    
}

Computer::~Computer()
{
    
}

void Computer::actionSelect()
{
    actionSelect0();
}

void Computer::actionSelect0()
{
    // Select move at random
    Pokemon* pokemon = getPokemon();
    
    if (pokemon->canMegaEvolve())
        setIntendedMove(MEGA);
    else
        setIntendedMove(FIGHT);
    
    pokemon->setIntendedMove(randInt(0, 3));
}

void Computer::actionSelect1()
{
    
}

void Computer::actionSelect2()
{
    
}

bool Computer::isComputer() const
{
    return true;
}