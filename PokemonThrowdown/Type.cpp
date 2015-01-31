//
//  Type.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Type.h"
#include "utilities.h" // toDouble()

constexpr Type::Effectiveness Type::effectivenesses[Type::MaxNumTypes][Type::MaxNumTypes];

double Type::getMultiplier(const Type& attackingType) const
{
    return toDouble(effectivenesses[attackingType.typeID][this->typeID]) / 100.0;
}