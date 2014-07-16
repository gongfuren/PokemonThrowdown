//
//  Player.h
//  pokemongame
//
//  Created by Ian Cordero on 6/10/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Player__
#define __PokemonThrowdown__Player__

#include <iostream>
#include "Trainer.h"
#include "constants.h"

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

class Player : public Trainer
// Represents a human controlled Trainer
{
public:
    Player(trainerdata h, Battle* battle);
    ~Player();
    
    virtual void actionSelect();
    virtual bool chooseRun();
    virtual bool choosePokemon();
    virtual bool isComputer() const;
    virtual bool trainerSummon(bool optional);
    bool chooseFight();
    
private:
};

#endif /* defined(__PokemonThrowdown__Player__) */
