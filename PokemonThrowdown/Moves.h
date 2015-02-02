//
//  Moves.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Moves__
#define __PokemonThrowdown__Moves__

#include <vector> 
#include <iostream>

#define vector std::vector
#define string std::string

class Move;

//
// Moves
// Organizes a set of moves.
//
class Moves
{
public:
    Moves();
    
    ~Moves();
    
    vector<Move*> getMoves() const;
    
    vector<string> getMoveNames() const;
    
    int getNumber() const;
    
private:
    vector<Move*> moves;
};

#undef vector
#undef string

#endif /* defined(__PokemonThrowdown__Moves__) */
