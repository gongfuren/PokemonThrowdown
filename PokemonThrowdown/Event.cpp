//
//  Event.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/22/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Event.h"

Event::Event(Pokemon* pokemon)
{
    m_pokemon = pokemon;
}

int Event::Intimidate(int eventID)
{
    if (eventID == OnSendOut)
    {
        return 1;
    }
    else
        return 0;
}