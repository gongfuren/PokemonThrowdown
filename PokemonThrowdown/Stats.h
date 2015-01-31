//
//  Stats.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Stats__
#define __PokemonThrowdown__Stats__

class Stat;

//
// Stats
// Manages a set of stats.
//
class Stats
{
public:
    Stat* getHP() const;
    
    Stat* getAtt() const;
    
    Stat* getDef() const;
    
    Stat* getSpA() const;
    
    Stat* getSpD() const;
    
    Stat* getSpe() const;
    
    Stat* getAcc() const;
    
    Stat* getEva() const;
    
    enum ID { HP = 0, Att, Def, SpA, SpD, Spe, Acc, Eva };
    static const int MaxNumStats = 8;
    
private:
    Stat* stats[MaxNumStats];
};

#endif /* defined(__PokemonThrowdown__Stats__) */
