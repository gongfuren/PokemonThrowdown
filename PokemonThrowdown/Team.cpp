//
//  Team.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Team.h"
#include "Pokemon.h"
#include <vector> 
#include <iostream>

using namespace std;

Team::Team()
{
    Pokemon* first = new Pokemon();
    pokemon.push_back(first);
    pokemon.push_back(new Pokemon());
    pokemon.push_back(new Pokemon());
    active.push_back(first);
}

Team::~Team()
{
    for (Pokemon* p : pokemon)
    {
        delete p;
    }
}

vector<Pokemon*> Team::getActive() const
{
    return active;
}

vector<Pokemon*> Team::getPokemon() const
{
    return pokemon;
}

vector<string> Team::getPokemonNames() const
{
    vector<string> names;
    for (Pokemon* p : pokemon)
    {
        names.push_back(p->getName());
    }
    return names;
}