//
//  Moves.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include <vector>
#include "Moves.h"
#include "Move.h"
#include <iostream>
#include "utilities.h"

using namespace std;

Moves::Moves()
{
    moves.push_back(new Move());
}

Moves::~Moves()
{
    for (Move* move : moves)
    {
        delete move;
    }
}

vector<Move*> Moves::getMoves() const
{
    return moves;
}

vector<string> Moves::getMoveNames() const
{
    vector<string> strings;
    for (Move* move : moves)
    {
        strings.push_back(move->getName());
    }
    return strings;
}

int Moves::getNumber() const
{
    return toInt(moves.size());
}