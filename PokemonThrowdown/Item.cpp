//
//  Item.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/8/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Item.h"
#include "constants.h"
#include "strings.h"

Item::Item(int ID)
{
    m_ID = ID;
    m_age = -1;
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

Pokemon* Item::getHolder() const
{
    return m_holder;
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
// i.e. Flame Orb
{
    
}