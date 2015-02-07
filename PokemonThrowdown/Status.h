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

#undef vector

#endif /* defined(__PokemonThrowdown__Status__) */
