//
//  Status.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/1/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Status__
#define __PokemonThrowdown__Status__

#include "Reactor.h"
#include <vector> 
#include "StatusBox.h"

#define vector std::vector

class Condition;
class Volatile;

class Status : public Reactor
{
public:
    Status(Pokemon* pokemon);
    
    Condition* getCondition() const;
    
    vector<Volatile*> getVolatiles() const;
    
private:
    Condition* condition;
    vector<Volatile*> volatiles;
};

class Condition : public Reactor
{
public:
    Condition(Pokemon* pokemon);
    
    virtual StatusBox::StatusToken getToken() const = 0;
    
private:
    int age;
};

class Volatile : public Reactor
{
public:
    StatusBox::VolatileToken getToken() const;
    
private:
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
    
};

#undef vector

#endif /* defined(__PokemonThrowdown__Status__) */
