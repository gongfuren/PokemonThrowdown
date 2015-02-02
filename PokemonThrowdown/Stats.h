//
//  Stats.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Stats__
#define __PokemonThrowdown__Stats__

#include <vector> 

#define vector std::vector

class Stat;

//
// Stats
// Manages a set of stats.
//
class Stats
{
public:
    enum ID
    { HP = 0, Att, Def, SpA, SpD, Spe, Acc, Eva
    };
    
    Stats();
    
    ~Stats();
    
    Stat* getHP() const;
    
    Stat* getAtt() const;
    
    Stat* getDef() const;
    
    Stat* getSpA() const;
    
    Stat* getSpD() const;
    
    Stat* getSpe() const;
    
    Stat* getAcc() const;
    
    Stat* getEva() const;
    
private:
    vector<Stat*> stats;
};

#undef vector

#endif /* defined(__PokemonThrowdown__Stats__) */
