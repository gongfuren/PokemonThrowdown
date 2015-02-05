//
//  exceptions.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "exceptions.h"
#include <iostream>

using namespace std;

LogicException::LogicException(string message)
: logic_error(message)
{
}

HPMultiplierException::HPMultiplierException()
: LogicException("Cannot ask HPStat for its multiplier.")
{
}

NavigationException::NavigationException(string message)
: LogicException(message)
{
}

BattleControlFlowException::BattleControlFlowException()
: LogicException("Exception in battle control flow.")
{
}

BattleControlFlowException::BattleControlFlowException(string message)
: LogicException(message)
{
}

ZombiePokemonException::ZombiePokemonException()
: LogicException("Attempting to manipulate a fainted (zombie) Pokemon -- uh oh!")
{
}

RuntimeException::RuntimeException(string message)
: runtime_error(message)
{
}

ArrayOutOfBoundsException::ArrayOutOfBoundsException()
: RuntimeException("Attempted to access an element outside of an array.")
{
}

InvalidPointerException::InvalidPointerException()
: RuntimeException("Passed invalid pointer to function.")
{
}

InvalidPointerException::InvalidPointerException(string message)
: RuntimeException(message)
{
}

PokemonTeamPointerException::PokemonTeamPointerException()
: InvalidPointerException("A problem occurred while manipulating Pokemon pointers.")
{
}

PokemonTeamPointerException::PokemonTeamPointerException(string message)
: InvalidPointerException(message)
{
}