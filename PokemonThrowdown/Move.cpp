//
//  Move.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include <iostream>
#include "Move.h"
#include <vector>
#include "Moves.h"
#include "Type.h"
#include "Pokemon.h"
#include "Types.h"
#include "utilities.h"
#include "Stats.h"
#include "Stat.h"
#include "Slot.h"

using namespace std;

Move::Move(Moves* moves)
{
    name = "Thunderbolt";
    power = 90;
    accuracy = 100;
    pP = 15;
    category = Special;
    priority = RegularPriority;
    type = new Type();
    hits = 1;
    this->moves = moves;
}

string Move::getName() const
{
    return name;
}

int Move::getPower() const
{
    return power;
}

int Move::getAccuracy() const
{
    return accuracy;
}

int Move::getPP() const
{
    return pP;
}

Move::Category Move::getCategory() const
{
    return category;
}

Move::Priority Move::getPriority() const
{
    return priority;
}

const vector<Slot*> Move::getTargets() const
{
    return targets;
}

void Move::setTarget(Slot* target)
{
    clearTargets();
    targets.push_back(target);
}

void Move::clearTargets()
{
    targets.clear();
}

Type* Move::getType() const
{
    return type;
}

Pokemon* Move::getPokemon() const
{
    return moves->getPokemon();
}

void Move::execute()
{
    for (Slot* slot : targets)
    {
        Pokemon* attacker = getPokemon();
        Pokemon* target = slot->getPokemon();
        
        if (target == nullptr)
        {
            continue;
        }
        
        // Calculate type bonuses, move power, mastery, critical
        const double TypeBoost = target->getTypes()->getMultiplier(type);
        const double SameTypeAttackBonus = attacker->getTypes()->getSameTypeAttackBonus(type);
        const double MovePower = power;
        const double Mastery = toDouble(randInt(85, 100)) / 100.0;
        const double Critical = attacker->getCriticalMultiplier();
        const double OtherBoosts = 1.0;
        
        const double AttackMultiplier = 1.0;
        const double SpecialAttackMultiplier = 1.0;
        const double DefenseMultiplier = 1.0;
        const double SpecialDefenseMultiplier = 1.0;
        
        // Construct modifier
        const double Modifier = TypeBoost * SameTypeAttackBonus * Critical * Mastery * OtherBoosts;
        
        // Calculate ratio of attack to target's defenses
        const double AttackOverDefense = (category == Move::Physical) ? toDouble(attacker->getStats()->getAtt()->getEffectiveValue()) * AttackMultiplier / (toDouble(target->getStats()->getDef()->getEffectiveValue()) * DefenseMultiplier) : toDouble(attacker->getStats()->getSpA()->getEffectiveValue()) * SpecialAttackMultiplier / (toDouble(target->getStats()->getSpD()->getEffectiveValue()) * SpecialDefenseMultiplier);
        
        // Construct damage amount
        const double Damage = ((2.0 * attacker->getLevel() + 10.0) / 250.0) * AttackOverDefense * MovePower + 2.0;
        
        // Apply modifier
        const double TotalDamage = Damage * Modifier;
        
        // Finally decrement HP
        target->getStats()->getHP()->lower(toInt(TotalDamage));
    }
}