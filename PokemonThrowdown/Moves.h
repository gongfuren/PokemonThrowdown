//
//  Moves.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Moves__
#define __PokemonThrowdown__Moves__

class Move;

//
// Moves
// Organizes a set of moves.
//
class Moves
{
public:
    static const int MaxNumMoves = 4;
    
private:
    Move* moves[MaxNumMoves];
};

#endif /* defined(__PokemonThrowdown__Moves__) */