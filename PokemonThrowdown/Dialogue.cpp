//
//  Dialogue.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/31/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Dialogue.h"

using namespace std;

Dialogue::Dialogue(string text)
{
    this->text = text;
}

string Dialogue::getText() const
{
    return text;
}

Question::Question(string text)
: Dialogue(text)
{
}