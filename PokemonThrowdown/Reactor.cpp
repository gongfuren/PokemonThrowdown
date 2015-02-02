//
//  Reactor.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Reactor.h"

Reactor::Reactor(Pokemon* pokemon)
{
    this->pokemon = pokemon;
}

Pokemon* Reactor::getPokemon() const
{
    return pokemon;
}