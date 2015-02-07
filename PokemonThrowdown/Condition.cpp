//
//  Condition.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Condition.h"
#include "StatusBox.h"

Condition::Condition(Pokemon* pokemon)
: Reactor(pokemon)
{
}

Condition::~Condition()
{
}

StatusBox::StatusToken HealthyCondition::getToken() const
{
    return StatusBox::StatusToken::Healthy;
}

HealthyCondition::HealthyCondition(Pokemon* pokemon)
: Condition(pokemon)
{
}

FaintCondition::FaintCondition(Pokemon* pokemon)
: Condition(pokemon)
{
}

StatusBox::StatusToken FaintCondition::getToken() const
{
    return StatusBox::StatusToken::Faint;
}