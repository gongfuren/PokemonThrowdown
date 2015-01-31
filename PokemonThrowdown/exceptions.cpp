//
//  exceptions.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "exceptions.h"

LogicException::LogicException(std::string message)
: std::logic_error(message)
{
}

HPMultiplierException::HPMultiplierException()
: LogicException("Cannot ask HPStat for its multiplier.")
{
}