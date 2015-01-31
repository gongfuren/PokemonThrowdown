//
//  Alert.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Alert.h"

Alert::Alert(std::string text)
{
    this->text = text;
}

std::string Alert::getText() const
{
    return text;
}