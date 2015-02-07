//
//  Slot.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/3/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Slot.h"
#include <iostream>

Slot::Slot(Pokemon* pokemon, Team* team)
{
    this->pokemon = pokemon;
    this->team = team;
}

Pokemon* Slot::getPokemon() const
{
    return pokemon;
}

void Slot::setPokemon(Pokemon* pokemon)
{
    this->pokemon = pokemon;
}

void Slot::clearPokemon()
{
    this->pokemon = nullptr;
}