//
//  Item.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Item__
#define __PokemonThrowdown__Item__

#include "Reactor.h"

class Pokemon;

//
// Item
// Represents a Pokemon item.
// Pokemon can optionally hold an item to restore HP or activate certain effects
// during battle.
//
class Item : public Reactor
{
public:
    Item(Pokemon* pokemon);
};

#endif /* defined(__PokemonThrowdown__Item__) */
