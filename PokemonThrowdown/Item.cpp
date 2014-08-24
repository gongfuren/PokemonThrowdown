//
//  Item.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/8/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Item.h"
#include "Pokemon.h"
#include "itemdata.h"
#include "constants.h"
#include "strings.h"

Item::Item(int ID, Pokemon* pokemon)
{
    m_ID = ID;
    m_age = -1;
    m_pokemon = pokemon;
}

Item::~Item()
{
    
}

int Item::getID() const
{
    return m_ID;
}

int Item::getAge() const
{
    return m_age;
}

string Item::getName() const
{
    return itemStrings[m_ID];
}

Pokemon* Item::getPokemon() const
{
    return m_pokemon;
}

bool Item::restrictsChoice() const
{
    if (m_ID == HChoiceBand || m_ID == HChoiceSpecs || m_ID == HChoiceScarf)
        return true;
    else
        return false;
}

void Item::incrementAge()
{
    m_age++;
}

void Item::resetAge()
{
    m_age = 0;
}

void Item::applyEffect()
{
    if (getID() == HLeftovers)
    {
        getPokemon()->increaseHP(0.0625 * getPokemon()->getStatsStatus(HPStat));
        cout << getPokemon()->getName() << " restored HP using its " << getName() << "!" << endl;
    }
    else if (getID() == HBlackSludge)
    {
        if (getPokemon()->getType1() == PoisonType || getPokemon()->getType2() == PoisonType)
        {
            getPokemon()->increaseHP(0.0625 * getPokemon()->getStatsStatus(HPStat));
            cout << getPokemon()->getName() << " restored HP using its " << getName() << "!" << endl;
        }
        else
        {
            getPokemon()->increaseHP(0.125 * getPokemon()->getStatsStatus(HPStat));
            cout << getPokemon()->getName() << " was hurt by " << getName() << "!" << endl;
        }
    }
}

bool Item::endOfTurn()
{
    if (m_age == -1)
        m_age = 0;
    
    applyEffect();
    incrementAge();
    
    return true;
}