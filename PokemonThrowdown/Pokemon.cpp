//
//  Pokemon.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Pokemon.h"
#include "Moves.h"
#include "Stats.h"
#include "Types.h"
#include "Ability.h"
#include "Item.h"
#include <iostream>
#include "Status.h"
#include "Team.h"
#include "Move.h"
#include "utilities.h" // toDouble()
#include "Stat.h"

using namespace std;

Pokemon::Pokemon(Team* team)
{
    name = "Pikachu";
    nickname = nullptr;
    moves = new Moves(this);
    stats = new Stats(this);
    types = new Types(this);
    ability = new Ability(this);
    item = new Item(this);
    gender = Male;
    status = new Status(this);
    level = 100;
    this->team = team;
}

Pokemon::~Pokemon()
{
    delete nickname;
    delete moves;
    delete stats;
    delete types;
    delete ability;
    delete item;
    delete status;
}

string Pokemon::getName() const
{
    return name;
}

string* Pokemon::getNickname() const
{
    return nickname;
}

Moves* Pokemon::getMoves() const
{
    return moves;
}

Stats* Pokemon::getStats() const
{
    return stats;
}

Types* Pokemon::getTypes() const
{
    return types;
}

Ability* Pokemon::getAbility() const
{
    return ability;
}

Item* Pokemon::getItem() const
{
    return item;
}

Pokemon::Gender Pokemon::getGender() const
{
    return gender;
}

Status* Pokemon::getStatus() const
{
    return status;
}

int Pokemon::getLevel() const
{
    return level;
}

string Pokemon::getFullName() const
{
    string name;
    name += this->name;
    if (nickname != nullptr)
    {
        name += " " + *nickname;
    }
    return name;
}

string Pokemon::description(Pokemon::Gender gender)
{
    switch (gender)
    {
        case Pokemon::Male:
            return "Male";
        case Pokemon::Female:
            return "Female";
        default:
            return "Genderless";
    }
}

string Pokemon::shortDescription(Pokemon::Gender gender)
{
    switch (gender)
    {
        case Pokemon::Male:
            return "M";
        case Pokemon::Female:
            return "F";
        default:
            return "-";
    }
}

Trainer* Pokemon::getTrainer() const
{
    return team->getTrainer();
}

double Pokemon::getCriticalMultiplier() const
{
    const double CriticalRate = 0.0625;
    const double DiceRoll = toDouble(randInt(0, 9999)) / 10000.0;
    
    if (DiceRoll < CriticalRate)
    {
        // TEMPORARY FIX TODO!!!
        println("A critical hit!");
        
        return 1.50;
    }
    else
    {
        return 1.00;
    }
}