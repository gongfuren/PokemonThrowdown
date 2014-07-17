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
