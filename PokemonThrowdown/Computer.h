//
//  Computer.h
//  pokemongame
//
//  Created by Ian Cordero on 6/15/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Computer__
#define __pokemongame__Computer__

#include <iostream>
#include "Trainer.h"
#include "constants.h"

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

class Computer : public Trainer
// Represents a computer controlled Trainer
{
public:
    Computer(TrainerData h, Battle* battle);
    ~Computer();
    
    virtual void actionSelect();
    void actionSelect(int level);
    virtual bool chooseRun();
    virtual bool isComputer() const;
    virtual bool choosePokemon();
    virtual bool trainerSummon(bool optional);
    
private:
    int m_difficulty;
};

#endif /* defined(__pokemongame__Computer__) */
