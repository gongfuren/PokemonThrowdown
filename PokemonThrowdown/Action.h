//
//  Action.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/1/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Action__
#define __PokemonThrowdown__Action__

//
// Action
// A token representing a player's intended move.
//
struct Action
{
    enum Type
    {
        Fight, Bag, Pokemon, Run
    };
    
    Action(Type type, int value);
    
    Type type;
    int value;
    bool megaEvolution;
    
    static const int DontCare = -1;
};

#endif /* defined(__PokemonThrowdown__Action__) */
