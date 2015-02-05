//
//  exceptions.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__exceptions__
#define __PokemonThrowdown__exceptions__

#include <stdexcept>
#include <iostream>

#define string std::string
#define logic_error std::logic_error
#define runtime_error std::runtime_error

class LogicException : public logic_error
{
public:
    LogicException(string message);
};

class HPMultiplierException : public LogicException
{
public:
    HPMultiplierException();
};

class NavigationException : public LogicException
{
public:
    NavigationException(string message);
};

class BattleControlFlowException : public LogicException
{
public:
    BattleControlFlowException();
    BattleControlFlowException(string message);
};

class ZombiePokemonException : public LogicException
{
public:
    ZombiePokemonException();
};

class RuntimeException : public runtime_error
{
public:
    RuntimeException(string message);
};

class ArrayOutOfBoundsException : public RuntimeException
{
public:
    ArrayOutOfBoundsException();
};

class InvalidPointerException : public RuntimeException
{
public:
    InvalidPointerException();
    InvalidPointerException(string message);
};

class PokemonTeamPointerException : public InvalidPointerException
{
public:
    PokemonTeamPointerException();
    PokemonTeamPointerException(string message);
};

#undef logic_error
#undef runtime_error
#undef string

#endif /* defined(__PokemonThrowdown__exceptions__) */
