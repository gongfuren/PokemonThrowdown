//
//  Move.cpp
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Move.h"
#include "MoveData.h"
#include "constants.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "Battle.h"

#include <iostream>
using namespace std;

Move::Move(int moveID, Pokemon* pokemon)
: m_name(""), m_type(NoType), m_damage(0), m_accuracy(0), m_effect(MNoEffect),
m_PP(0), m_currentPP(0), m_pokemon(pokemon), m_description(""),
m_target(Opponent), m_ID(moveID), m_PPUps(0), m_contact(false), m_age(0)
{
    // Standard Initialization:
    
    standardInit(moveID);
}

Move::~Move()
{
}

void Move::standardInit(int moveID)
{
    m_name = movelib[moveID].name;
    m_type = movelib[moveID].type;
    m_damage =  movelib[moveID].damage;
    m_accuracy = movelib[moveID].accuracy;
    m_PP = movelib[moveID].PP;
    m_moveType = movelib[moveID].moveType;
    m_effect = movelib[moveID].effect;
    m_description = movelib[moveID].description;
    m_target = movelib[moveID].target;
    m_contact = movelib[moveID].contact;
    m_ID = moveID;
    
    m_currentPP = movelib[moveID].PP;
    m_age = 0;
    m_PPUps = 3;
}

bool Move::getContact() const
{
    return m_contact;
}

Pokemon* Move::getPokemon() const
{
    return m_pokemon;
}

MoveEffect Move::getEffect() const
{
    return m_effect;
}

string Move::getDescription() const
{
    return m_description;
}

string Move::getName() const
{
    return m_name;
}

Type Move::getType() const
{
    return m_type;
}

int Move::getDamage() const
{
    return m_damage;
}

int Move::getAccuracy() const
{
    return m_accuracy;
}

MoveType Move::getMoveType() const
{
    return m_moveType;
}

int Move::getPP() const
{
    return m_PP;
}

int Move::getID() const
{
    return m_ID;
}

int Move::getCurrentPP() const
{
    return m_currentPP;
}

void Move::decCurrentPP()
{
    m_currentPP--;
}

MoveTarget Move::getTarget() const
{
    return m_target;
}

int Move::getAge() const
{
    return m_age;
}

void Move::incAge()
{
    m_age++;
}

void Move::resetAge()
{
    m_age = 0;
}

bool Move::isThrash() const
{
    switch (m_ID)
    {
        default:
            return false;
        case 200:
        case 80:
        case 37:
            return true;
    }
}

int Move::detPriorityScore() const
{
    switch (getEffect())
    {
        case MRoar:
            return -7;
        case MTrickRoom:
            return -6;
        case MCounter:
            return -5;
        case MFocusPunch:
        case MVitalThrow:
            return -4;
        case MSuckerPunch:
            return 1;
        case MMoveFirst:
            return 2;
        case MMoveFirst2:
            return 3;
        case MProtect:
        case MShield:
            return 6;
        default:
            return 0;
    }
}

bool Move::determineFailure(Pokemon* target) const
{
    Battle* battle = getPokemon()->getTrainer()->getBattle();
    Move* targetMove = target->getMove(target->getIntendedMove());
    bool failed = false;
    
    if (getEffect() == MSuckerPunch)
        // Sucker punch
    {
        if (!(targetMove->isAttack()
              && (target->getTrainer()->getIntendedMove() == FIGHT
                  || target->getTrainer()->getIntendedMove() == MEGA))
            || targetMove->detPriorityScore() > detPriorityScore())
            // Trainer isn't attacking and pokemon isn't readying attack
            // or opponent already attacked
            failed = true;
    }
    else if ((m_effect == MRain && battle->getWeather() == Rain) ||
             (m_effect == MSun && battle->getWeather() == Sunny) ||
             (m_effect == MSandstorm && battle->getWeather() == Sandstorm) ||
             (m_effect == MHail && battle->getWeather() == Hail))
        // Casting weather that already exists
    {
            failed = true;
    }
    else if (getPokemon()->usedProtect(1))
        // Successive protects
    {
        int successChance = 100;
        
        for (int i = 1; getPokemon()->usedProtect(i); i++)
            // How many turns in a row was Protect used?
        {
            successChance /= 2;
        }
        
        if (randInt(0, 99) < successChance)
            ;
        else
            failed = true;
}
    
    return failed;
}

bool Move::isAttack() const
{
    return (m_moveType == Physical || m_moveType == Special);
}