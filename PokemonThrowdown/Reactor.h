//
//  Reactor.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/22/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Reactor__
#define __PokemonThrowdown__Reactor__

#include <iostream>
#include "Event.h"

class Reactor
{
public:
    Reactor(int(Event::* reaction)(int));
    
private:
    int(Event::* m_reaction)(int);
};

#endif /* defined(__PokemonThrowdown__Reactor__) */
