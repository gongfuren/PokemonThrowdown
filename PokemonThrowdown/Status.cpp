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

Status::~Status()
{
    delete condition;
    
    for (Volatile* v : volatiles)
    {
        delete v;
    }
}

Condition* Status::getCondition() const
{
    return condition;
}

void Status::setCondition(Condition* condition)
{
    clearCondition();
    this->condition = condition;
}

void Status::clearCondition()
{
    delete condition;
    condition = nullptr;
}

vector<Volatile*> Status::getVolatiles() const
{
    return volatiles;
}

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