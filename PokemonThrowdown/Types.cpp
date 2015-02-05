//
//  Types.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Types.h"
#include "Type.h"
#include "utilities.h" // println()
#include "Pokemon.h"
#include "Trainer.h"

Types::Types(Pokemon* pokemon)
{
    types.push_back(new Type(Type::Electric));
    this->pokemon = pokemon;
}

Types::~Types()
{
    for (Type* type : types)
    {
        delete type;
    }
}

double Types::getMultiplier(const Type* attackingType) const
{
    double multiplier = 1.0;
    
    for (Type* type : types)
    {
        multiplier *= type->getMultiplier(attackingType);
    }
    
    // TEMPORARY FIX TODO!!!
    if (multiplier == 0.0)
    {
        println("It doesn't affect " + pokemon->getTrainer()->getTitleAndName() + "'s " + pokemon->getFullName() + ".");
    }
    else if (multiplier < 1.0)
    {
        println("It's not very effective...");
    }
    else if (multiplier > 1.0)
    {
        println("It's super effective!");
    }
    
    return multiplier;
}

double Types::getSameTypeAttackBonus(const Type* attackType) const
{
    for (Type* type : types)
    {
        if (type->getID() == attackType->getID())
        {
            return 1.5;
        }
    }
    
    return 1.0;
}