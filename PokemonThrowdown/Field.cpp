//
//  Field.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/7/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Field.h"
#include "Side.h"
#include "Game.h"
#include "Battle.h"
#include "strings.h"
#include "utilities.h"
#include "Settings.h"
using namespace std;

Field::Field(Battle* battle, int X, int Y)
: Zone(X, Y, 1, 2)
{
    m_battle = battle;
    m_location = static_cast<Location>(getBattle()->getGame()->getSettings()->getLocationID());
    
    if (getBattle()->getGame()->getSettings()->getWeatherID() == RandomWeather)
        m_weather = static_cast<Weather>(randInt(NoWeather, Twilight));
    else
        m_weather = static_cast<Weather>(getBattle()->getGame()->getSettings()->getWeatherID());
    
    for (int i = 0; i < NUMSIDES; i++)
        m_sides[i] = new Side(this, X, Y);
}

Field::~Field()
{
    for (int i = 0; i < NUMSIDES; i++)
        delete m_sides[i];
}

Side* Field::getSide(int whichSide) const
{
    return m_sides[whichSide];
}

Weather Field::getWeather() const
{
    return m_weather;
}

Terrain Field::getTerrain() const
{
    return m_terrain;
}

Location Field::getLocation() const
{
    return m_location;
}

Battle* Field::getBattle() const
{
    return m_battle;
}

void Field::initializeWeather()
{
    if (m_weather != NoWeather)
    {
        m_weatherTurns = 5;
        cout << weatherStartStrings[m_weather] << endl;
    }
}

void Field::initializeWeather(Weather weather)
{
    m_weather = weather;
    initializeWeather();
}

void Field::weatherContinue()
{
    if (m_weather != NoWeather)
    {
        if (--m_weatherTurns == 0)
        {
            cout << weatherEndStrings[m_weather] << endl;
            
            m_weather = NoWeather;
            
            return;
        }
        
        cout << weatherContStrings[m_weather] << endl;
        
        for (int i = 0; i < NUMSIDES; i++)
            m_sides[i]->weatherEffect(m_weather);
    }
}

void Field::initializeTerrain(Terrain terrain)
{
    m_terrain = terrain;
}