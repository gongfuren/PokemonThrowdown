//
//  Side.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/7/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Side.h"
#include "Slot.h"
#include "constants.h"

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

Side::Side(Field* field)
{
    m_field = field;
    m_numTrainers = 0;
    
    for (int i = 0; i < MAXPOKEMONPERPLAYER; i++)
        m_slots[i] = new Slot(this);
}

Side::~Side()
{
    for (int i = 0; i < MAXPOKEMONPERPLAYER; i++)
        delete m_slots[i];
}

Slot* Side::getSlot(int whichSlot) const
{
    return m_slots[whichSlot];
}

EntryHazard Side::getHazards() const
{
    // Temp
    return NoHazard;
}

Screen Side::getScreens() const
{
    // Temp
    return NoScreen;
}

Trainer* Side::getTrainer(int whichTrainer) const
{
    return m_trainers[whichTrainer];
}

Field* Side::getField() const
{
    return m_field;
}

void Side::addHazard(EntryHazard hazard)
{
    m_hazards.push_back(hazard);
}

bool Side::hasHazard(EntryHazard hazard) const
{
    return listContains(m_hazards, hazard);
}

void Side::addScreen(Screen screen)
{
    m_screens.push_back(screen);
}

bool Side::hasScreen(Screen screen) const
{
    return listContains(m_screens, screen);
}

void Side::weatherEffect(Weather weather)
{
    for (int i = 0; i < MAXPOKEMONPERPLAYER; i++)
        m_slots[i]->weatherEffect(weather);
}

void Side::addTrainer(Trainer* trainer)
{
    m_trainers[m_numTrainers++] = trainer;
}

void Side::removeHazard(EntryHazard hazard)
{
    m_hazards.remove(hazard);
}

void Side::removeScreen(Screen screen)
{
    m_screens.remove(screen);
}