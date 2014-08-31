//
//  Side.h
//  pokemongame
//
//  Created by Ian Cordero on 6/7/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Side__
#define __PokemonThrowdown__Side__

#include <iostream>
#include <list>
#include "constants.h"
#include "Zone.h"

class Slot;
class Field;
class Trainer;

class Side : public Zone
// Represents one side of the battlefield (there are always two sides) and
// the state of a respective side
{
public:
    Side(Field* field, int X, int Y);
    ~Side();
    
    Slot* getSlot(int whichSlot = 0) const;
    EntryHazard getHazards() const;
    Screen getScreens() const;
    Trainer* getTrainer(int whichTrainer = 0) const;
    
    Field* getField() const;
    
    void addHazard(EntryHazard hazard);
    bool hasHazard(EntryHazard hazard) const;
    void addScreen(Screen screen);
    bool hasScreen(Screen screen) const;
    void weatherEffect(Weather weather);
    void addTrainer(Trainer* trainer);
    void removeHazard(EntryHazard hazard);
    void removeScreen(Screen screen);
    
private:
    Slot* m_slots[MAXPOKEMONPERPLAYER];
    std::list<EntryHazard> m_hazards;
    std::list<Screen> m_screens;
    Trainer* m_trainers[MAXPLAYERSPERSIDE];
    int m_numTrainers;
    
    Field* m_field;
};

#endif /* defined(__PokemonThrowdown__Side__) */
