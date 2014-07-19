//
//  Move.cpp
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Move.h"
#include "movedata.h"
#include "constants.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "Battle.h"

#include <iostream>
using namespace std;

Move::Move(int moveID, Pokemon* pokemon)
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
    
    m_pokemon = pokemon;
    m_currentPP = m_PP;
    m_age = 0;
    m_PPUps = 3;
}

Move::~Move()
{
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

bool Move::decrementCurrentPP()
{
    if (m_currentPP == 0)
        return false;
    else
    {
        m_currentPP--;
        return true;
    }
}

MoveTarget Move::getTarget() const
{
    return m_target;
}

int Move::getAge() const
{
    return m_age;
}

void Move::incrementAge()
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

int Move::getPriorityScore() const
{
    int m;
    
    switch (getEffect())
    {
        case MTrickRoom:
            m = -7;
            break;
        case MRoar:
            m = -6;
            break;
        case MCounter:
            m = -5;
            break;
        case MFocusPunch:
            m = -3;
            break;
        case MVitalThrow:
            m = -1;
            break;
        case MSuckerPunch:
        case MMoveFirst:
            m = 1;
            break;
        case MMoveFirst2:
            m = 2;
            break;
        case MShield:
            m = 3;
            break;
        case MProtect:
            m = 4;
            break;
        default:
            m = 0;
            break;
    }
    
    // Prankster and a status move: enhanced priority
    if (getPokemon()->getAbility() == PPrankster && getMoveType() == Status)
        m++;
    
    return m;
}

bool Move::determineFailure(Pokemon* target) const
{
    Pokemon* user = getPokemon();
    Move* userMove = user->getMove(user->getIntendedMove());
    MoveEffect effect = userMove->getEffect();
    Battle* battle = getPokemon()->getTrainer()->getBattle();
    Move* targetMove = target->getMove(target->getIntendedMove());
    bool failed = false;
    
    // Sucker Punch
    if (getEffect() == MSuckerPunch)
    {
        // Target isn't readying an attack
        if (!(targetMove->isAttack()
              && (target->getTrainer()->getIntendedMove() == FightDecision
                  || target->getTrainer()->getIntendedMove() == MegaDecision))
            || targetMove->getPriorityScore() > getPriorityScore())
            failed = true;
    }
    // Casting weather that already exists
    else if ((m_effect == MRain && battle->getWeather() == Rain) ||
             (m_effect == MSun && battle->getWeather() == Sunny) ||
             (m_effect == MSandstorm && battle->getWeather() == Sandstorm) ||
             (m_effect == MHail && battle->getWeather() == Hail))
    {
            failed = true;
    }
    // Successive protects
    else if (getPokemon()->usedProtect(1)
             && (effect == MProtect || effect == MShield))
    {
        int successChance = 100;
        
        // How many turns in a row was Protect used? Halve success rate for
        // each turn
        for (int i = 1; getPokemon()->usedProtect(i); i++)
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