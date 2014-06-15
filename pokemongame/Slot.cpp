//
//  Slot.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/7/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Slot.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "constants.h"

Slot::Slot(Side* side)
{
    m_side = side;
}

Slot::~Slot()
{
    
}

Pokemon* Slot::getPokemon() const
{
    return m_pokemon;
}

Side* Slot::getSide() const
{
    return m_side;
}

void Slot::weatherEffect(Weather weather)
{
    Type type1 = m_pokemon->getType1();
    Type type2 = m_pokemon->getType2();
    Trainer* trainer = m_pokemon->getTrainer();
    
    if (m_pokemon->isDead())
        return;
    
    if (weather == Sandstorm && !(type1 == RockType || type2 == RockType ||
                                    type1 == GroundType || type2 == GroundType ||
                                    type1 == SteelType || type2 == SteelType))
    {
        m_pokemon->lowerHP(static_cast<double>(m_pokemon->getBStats(HPSTAT)) * (0.0625));
        cout << trainer->getTitle() << " " << trainer->getName() << "'s "
        << m_pokemon->getName() << " is buffetted by the sandstorm!" << endl;
    }
    
    if (weather == Hail && !(type1 == IceType || type2 == IceType))
    {
        m_pokemon->lowerHP(static_cast<double>(m_pokemon->getBStats(HPSTAT)) * (0.0625));
        
        cout << trainer->getTitle() << " " << trainer->getName() << "'s "
        << m_pokemon->getName() << " is pelted by the hail!" << endl;
    }
}

void Slot::fillSlot(Pokemon* pokemon)
{
    m_pokemon = pokemon;
}