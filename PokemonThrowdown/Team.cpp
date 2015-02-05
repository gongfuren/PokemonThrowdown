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
#include "exceptions.h"
#include "utilities.h"
#include "Slot.h"

using namespace std;

Team::Team(Trainer* trainer)
{
    Pokemon* first = new Pokemon(this);
    pokemon.push_back(first);
    pokemon.push_back(new Pokemon(this));
    pokemon.push_back(new Pokemon(this));
    slots.push_back(new Slot(first, this));
    this->trainer = trainer;
}

Team::~Team()
{
    for (Pokemon* p : pokemon)
    {
        delete p;
    }
    
    for (Slot* slot : slots)
    {
        delete slot;
    }
}

Slot* Team::getSlot() const
{
    return slots.at(FirstSlot);
}

vector<Slot*> Team::getSlots() const
{
    return slots;
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

void Team::setActive(Pokemon* pokemon)
{
    // Check that we haven't tried to switch a Pokemon with itself
    if (pokemon == slots.at(FirstSlot)->getPokemon())
    {
        throw PokemonTeamPointerException();
    }
    
    // Check that we are swapping with a Pokemon within this team
    int matchIndex = -1;
    
    for (int i = 0; i < this->pokemon.size(); i++)
    {
        if (pokemon == this->pokemon.at(i))
        {
            matchIndex = i;
            break;
        }
    }
    
    if (matchIndex < 0)
    {
        throw PokemonTeamPointerException();
    }
    
    // Swap active Pokemon
    slots.at(FirstSlot)->setPokemon(this->pokemon.at(matchIndex));
    swap(this->pokemon.at(FirstPokemon), this->pokemon.at(matchIndex));
}

void Team::clearActive()
{
    slots.at(FirstSlot)->clearPokemon();
}

Trainer* Team::getTrainer() const
{
    return trainer;
}