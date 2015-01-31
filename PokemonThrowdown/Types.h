//
//  Types.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Types__
#define __PokemonThrowdown__Types__

#include <vector>

class Type;

//
// Types
// Organizes a Pokemon's types
//
class Types
{
public:
    double getMultiplier(const Type& attackingType) const;
    
private:
    std::vector<Type*> types;
};

#endif /* defined(__PokemonThrowdown__Types__) */
