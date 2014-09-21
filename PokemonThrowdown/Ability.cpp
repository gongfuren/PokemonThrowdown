//
//  Ability.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/22/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Ability.h"
#include "strings.h"
#include "Pokemon.h"
#include <iostream>
using namespace std;

Ability::Ability(int ID, Pokemon* pokemon)
{
    m_name = abilityStrings[ID];
    m_pokemon = pokemon;
    m_ID = ID;
}

Ability::~Ability()
{
}

string Ability::getName() const
{
    return m_name;
}

int Ability::getID() const
{
    return m_ID;
}

Pokemon* Ability::getPokemon() const
{
    return m_pokemon;
}

void Ability::flash() const
{
    cout << getPokemon()->getName() << "'s " << abilityStrings[getID()] << ":" << endl;
}