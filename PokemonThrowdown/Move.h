//
//  Move.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Move__
#define __PokemonThrowdown__Move__

#include <iostream> 

#define string std::string

//
// Move
// Represents a Pokemon move.
//
class Move
{
public:
    enum Callback
    {
        BasePowerCallback = 0
    };
    
    Move();
    
    string getName() const;
    
    int getPower() const;
    
    int getAccuracy() const;
    
    int getPP() const;
    
private:
    string name;
    int power;
    int accuracy;
    int pP;
    enum { Physical = 0, Special, Status } type;
};

#undef string

#endif /* defined(__PokemonThrowdown__Move__) */
