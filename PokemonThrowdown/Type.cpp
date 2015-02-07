//
//  Type.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Type.h"
#include "utilities.h" // toDouble()

constexpr Type::Effectiveness Type::Effectivenesses[MaxNumTypes][MaxNumTypes];

Type::Type()
{
    iD = Electric;
}

Type::Type(Type::ID iD)
{
    this->iD = iD;
}

double Type::getMultiplier(const Type* attackingType) const
{
    return toDouble(Effectivenesses[this->iD][attackingType->iD]) / 100.0;
}

Type::ID Type::getID() const
{
    return iD;
}