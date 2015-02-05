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

//
// Status
// The whole, general status (NOT just the status condition) of a Pokemon. Includes
// its status condition and any volatile status conditions it may have.
//
class Status : public Reactor
{
public:
    Status(Pokemon* pokemon);
    
    ~Status();
    
    Condition* getCondition() const;
    
    void setCondition(Condition* condition);
    
    void clearCondition();
    
    vector<Volatile*> getVolatiles() const;
    
private:
    Condition* condition;
    vector<Volatile*> volatiles;
};

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

//
// Volatile
// Represents a volatile status condition on a Pokemon. These conditions are
// removed upon switching out.
//
class Volatile : public Condition
{
public:
    
private:
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

#undef vector

#endif /* defined(__PokemonThrowdown__Status__) */
