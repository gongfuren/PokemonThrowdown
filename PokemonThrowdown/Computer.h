//
//  Computer.h
//  pokemongame
//
//  Created by Ian Cordero on 6/15/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Computer__
#define __PokemonThrowdown__Computer__

#include <iostream>
#include "Trainer.h"
#include "constants.h"

class Computer : public Trainer
// Represents a computer controlled Trainer
{
public:
    Computer(trainerdata h, Battle* battle, int whichTrainer = 0);
    ~Computer();
    
    virtual void actionSelect();
    virtual bool chooseRun();
    virtual bool isComputer() const;
    virtual bool choosePokemon();
    virtual bool trainerSummon(bool optional, bool uTurn = false);
    
private:
    int m_difficulty;
};

#endif /* defined(__PokemonThrowdown__Computer__) */
