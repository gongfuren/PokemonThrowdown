//
//  Player.h
//  pokemongame
//
//  Created by Ian Cordero on 6/10/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Player__
#define __pokemongame__Player__

#include <iostream>
#include "Trainer.h"
#include "constants.h"

class Player : public Trainer
{
public:
    Player(TrainerData h, Battle* battle);
    ~Player();
    
    virtual void actionSelect();
    virtual bool isComputer() const;
    
private:
};

#endif /* defined(__pokemongame__Player__) */
