//
//  StatusBox.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/1/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "StatusBox.h"
#include "Pokemon.h"
#include <iostream> 
#include <vector> 
#include "Stats.h"
#include "Stat.h"
#include "Status.h"

using namespace std;

StatusBox::StatusBox(Pokemon* pokemon)
{
    hPBar = { pokemon->getStats()->getHP()->getStatus(), pokemon->getStats()->getHP()->getValue() };
    statusToken = new StatusToken(pokemon->getStatus()->getCondition()->getToken());
    level = pokemon->getLevel();
    gender = pokemon->getGender();
    name = pokemon->getFullName();
}

StatusBox::~StatusBox()
{
    delete statusToken;
}

int StatusBox::getHP() const
{
    return hPBar.magnitude;
}

int StatusBox::getHPTotal() const
{
    return hPBar.amplitude;
}

StatusBox::StatusToken* StatusBox::getStatusToken() const
{
    return statusToken;
}

vector<StatusBox::VolatileToken> StatusBox::getVolatileTokens() const
{
    return volatileTokens;
}

int StatusBox::getLevel() const
{
    return level;
}

Pokemon::Gender StatusBox::getGender() const
{
    return gender;
}

string StatusBox::getPokemonName() const
{
    return name;
}