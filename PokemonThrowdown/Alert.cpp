//
//  Alert.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Alert.h"

using namespace std;

Alert::Alert(string text)
{
    this->text = text;
}

string Alert::getText() const
{
    return text;
}