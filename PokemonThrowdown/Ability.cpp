//
//  Ability.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/22/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Ability.h"

Ability::Ability(int ID, Pokemon* pokemon)
{
    m_pokemon = pokemon;
    m_ID = ID;
}

Ability::~Ability()
{
}

int Ability::getID() const
{
    return m_ID;
}

Pokemon* Ability::getPokemon() const
{
    return m_pokemon;
}