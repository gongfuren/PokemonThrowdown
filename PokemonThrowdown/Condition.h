//
//  Condition.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Condition__
#define __PokemonThrowdown__Condition__

#include "Reactor.h" 
#include "StatusBox.h"

//
// Condition
// Represents a status condition on a Pokemon. A Pokemon may have only one
// status condition.
//
class Condition : public Reactor
{
public:
    Condition(Pokemon* pokemon);
    
    virtual ~Condition();
    
    virtual StatusBox::StatusToken getToken() const = 0;
    
protected:
    int age;
};

class HealthyCondition : public Condition
{
public:
    HealthyCondition(Pokemon* pokemon);
    
    StatusBox::StatusToken getToken() const;
};

class PoisonCondition : public Condition
{
public:
};

class ToxicCondition : public PoisonCondition
{
    
};

class BurnCondition : public Condition
{
    
};

class ParalyzeCondition : public Condition
{
    
};

class SleepCondition : public Condition
{
    
};

class FreezeCondition : public Condition
{
    
};

class FaintCondition : public Condition
{
public:
    FaintCondition(Pokemon* pokemon);
    
    StatusBox::StatusToken getToken() const;
};

#endif /* defined(__PokemonThrowdown__Condition__) */
