//
//  Menu.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Menu.h"

#define string std::string
#define vector std::vector
#define function std::function

Menu::Menu(string title, vector<string> options, function<void(int)> callback)
{
    this->title = title;
    this->options = options;
    this->callback = callback;
}

string Menu::getTitle() const
{
    return title;
}

vector<string> Menu::getOptions() const
{
    return options;
}

function<void(int)> Menu::getCallback() const
{
    return callback;
}

void Menu::executeCallback(int argument)
{
    callback(argument);
}