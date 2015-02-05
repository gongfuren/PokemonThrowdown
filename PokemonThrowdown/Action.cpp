//
//  Action.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/1/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Action.h"
#include "Pokemon.h"
#include "Move.h"
#include "exceptions.h"
#include "Stats.h"
#include "Stat.h"
#include "utilities.h"

Action::Action(Type type, Move* move, Item* item, Pokemon* pokemon, bool megaEvolution)
{
    this->type = type;
    this->move = move;
    this->item = item;
    this->pokemon = pokemon;
    this->megaEvolution = megaEvolution;
}

Action::Action(Move* move, Pokemon* pokemon, bool megaEvolution)
: Action(Action::Fight, move, nullptr, pokemon, megaEvolution)
{
}

Action::Action(Item* item)
: Action(Action::Bag, nullptr, item, nullptr)
{
}

Action::Action(Pokemon* pokemon)
: Action(Action::Switch, nullptr, nullptr, pokemon)
{
}

Action::Action()
: Action(Action::Run, nullptr, nullptr, nullptr)
{
}

bool Action::compare(const Action* action1, const Action* action2)
{
    if ((action1->type != Fight && action1->type != Switch) || (action2->type != Fight && action2->type != Switch))
    {
        throw InvalidPointerException();
    }
    
    const int priority1 = (action1->type == Switch) ? Move::SwitchOut : action1->move->getPriority();
    const int priority2 = (action2->type == Switch) ? Move::SwitchOut : action2->move->getPriority();
    
    if (priority1 != priority2)
    {
        return priority1 > priority2;
    }
    else
    {
        const int speed1 = (action1->type == Switch) ? 0 : action1->pokemon->getStats()->getSpe()->getEffectiveValue();
        const int speed2 = (action2->type == Switch) ? 0 : action2->pokemon->getStats()->getSpe()->getEffectiveValue();

        if (speed1 != speed2)
        {
            return speed1 > speed2;
        }
        else
        {
            return toBool(randInt(0, 1));
        }
    }
}