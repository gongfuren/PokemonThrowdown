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
    typeID = Electric;
}

double Type::getMultiplier(const Type& attackingType) const
{
    return toDouble(Effectivenesses[attackingType.typeID][this->typeID]) / 100.0;
}