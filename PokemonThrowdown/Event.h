//
//  Event.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/22/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Event__
#define __PokemonThrowdown__Event__

#include <iostream>

class Pokemon;

enum EventType
{
    OnBattleStart, OnSendOut, OnContact, OnTakeDamage, OnLowerStat
};

class Event
{
public:
    Event(Pokemon* pokemon);
    
    int Intimidate(int eventID);
    
private:
    Pokemon* m_pokemon;
};

#endif /* defined(__PokemonThrowdown__Event__) */
