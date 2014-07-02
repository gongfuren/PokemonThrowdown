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

class Computer : public Trainer
{
public:
    Computer(TrainerData h, Battle* battle);
    ~Computer();
    
    virtual void actionSelect();
    void actionSelect0();
    void actionSelect1();
    void actionSelect2();
    virtual bool isComputer() const;
    
private:
};

#endif /* defined(__pokemongame__Computer__) */
