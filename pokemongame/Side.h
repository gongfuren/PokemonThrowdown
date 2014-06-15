//
//  Side.h
//  pokemongame
//
//  Created by Ian Cordero on 6/7/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Side__
#define __pokemongame__Side__

#include <iostream>
#include <list>
#include "constants.h"

class Slot;
class Field;
class Trainer;

class Side
{
public:
    Side(Field* field);
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
    list<EntryHazard> m_hazards;
    list<Screen> m_screens;
    Trainer* m_trainers[MAXPLAYERSPERSIDE];
    int m_numTrainers;
    
    Field* m_field;
};

#endif /* defined(__pokemongame__Side__) */
