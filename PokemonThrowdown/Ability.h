//
//  Ability.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Ability__
#define __PokemonThrowdown__Ability__

#include "Reactor.h"

class Pokemon;

//
// Ability
// Each Pokemon has an ability that activates certain features based on events
// that occur during battle.
//
class Ability : public Reactor
{
public:
    Ability(Pokemon* pokemon);
};

#endif /* defined(__PokemonThrowdown__Ability__) */
