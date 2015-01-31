//
//  Types.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Types.h"
#include "Type.h"

double Types::getMultiplier(const Type& attackingType) const
{
    double multiplier = 1.0;
    
    for (Type* type : types)
    {
        multiplier *= type->getMultiplier(attackingType);
    }
    
    return multiplier;
}