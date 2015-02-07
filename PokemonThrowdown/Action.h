//
//  Action.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/1/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Action__
#define __PokemonThrowdown__Action__

#include <vector> 
#include "Printable.h"
#include <string>

#define vector std::vector
#define string std::string

class Move;
class Item;
class Pokemon;

//
// Action
// A token representing a player's intended move.
//
struct Action : public Printable
{
    enum Type
    {
        Fight, Bag, Switch, Run
    };
    
    Action(Type type, Move* move, Item* item, Pokemon* pokemon, bool megaEvolution = false);
    
    Action(Move* move, class Pokemon* pokemon, bool megaEvolution = false);
    
    Action(Item* item);
    
    Action(Pokemon* pokemon);
    
    Action();
    
    //
    // compare()
    // Returns true if action1 has more priority than action2.
    // If priorities are equal, judges based on speed.
    // If speeds are equal, returns random bool.
    //
    static bool compare(const Action* action1, const Action* action2);
    
    string description() const;
    
    Type type;
    Move* move;
    Item* item;
    Pokemon* pokemon;
    
    bool megaEvolution;
    
    static const int DontCare = -1;
    static const int PrimaryTarget = 0;
};

#undef vector
#undef string

#endif /* defined(__PokemonThrowdown__Action__) */
