//
//  Field.h
//  pokemongame
//
//  Created by Ian Cordero on 6/7/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Field__
#define __pokemongame__Field__

#include <iostream>
#include "constants.h"

class Side;
class Battle;

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

class Field
// Represents the battlefield and its current state
{
public:
    Field(Battle* battle);
    ~Field();
    
    Side* getSide(int whichSide) const;
    Weather getWeather() const;
    Terrain getTerrain() const;
    Location getLocation() const;
    
    Battle* getBattle() const;
    
    void initializeWeather();
    void initializeWeather(Weather weather);
    void weatherContinue();
    void initializeTerrain(Terrain terrain);
    
private:
    Side* m_sides[NUMSIDES];
    Weather m_weather;
    int m_weatherTurns;
    Terrain m_terrain;
    Location m_location;
    
    Battle* m_battle;
};


#endif /* defined(__pokemongame__Field__) */
