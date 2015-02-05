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

const string StatusBox::TokenLabels[StatusBox::NumStatusTokens] = { "OK ", "PSN", "BRN", "PRZ", "SLP", "FRZ", "FNT" };

StatusBox::StatusBox(Pokemon* pokemon, bool hPVisible)
{
    hPBar = { pokemon->getStats()->getHP()->getStatus(), pokemon->getStats()->getHP()->getValue(), hPVisible };
    statusToken = StatusToken(pokemon->getStatus()->getCondition()->getToken());
    level = pokemon->getLevel();
    gender = pokemon->getGender();
    name = pokemon->getFullName();
}

StatusBox::~StatusBox()
{
}

int StatusBox::getHP() const
{
    return hPBar.magnitude;
}

int StatusBox::getHPTotal() const
{
    return hPBar.amplitude;
}

bool StatusBox::getHPVisible() const
{
    return hPBar.visible;
}

StatusBox::StatusToken StatusBox::getStatusToken() const
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

string StatusBox::description(StatusBox::StatusToken token)
{
    return TokenLabels[token];
}