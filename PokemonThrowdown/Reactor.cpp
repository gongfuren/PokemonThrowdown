//
//  Reactor.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/22/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Reactor.h"

Reactor::Reactor(int(Event::* reaction)(int))
{
    m_reaction = reaction;
}