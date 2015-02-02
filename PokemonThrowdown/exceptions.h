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

class LogicException : public std::logic_error
{
public:
    LogicException(std::string message);
};

class HPMultiplierException : public LogicException
{
public:
    HPMultiplierException();
};

class NavigationException : public LogicException
{
public:
    NavigationException(std::string message);
};

#endif /* defined(__PokemonThrowdown__exceptions__) */
