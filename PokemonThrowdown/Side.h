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

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

class Side
// Represents one side of the battlefield (there are always two sides) and
// the state of a respective side
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
