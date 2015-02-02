//
//  Status.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/1/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Status.h"
#include "Reactor.h"
#include <vector> 

using namespace std;

Status::Status(Pokemon* pokemon)
: Reactor(pokemon)
{
    condition = new HealthyCondition(pokemon);
}

Condition* Status::getCondition() const
{
    return condition;
}

vector<Volatile*> Status::getVolatiles() const
{
    return volatiles;
}

Condition::Condition(Pokemon* pokemon)
: Reactor(pokemon)
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