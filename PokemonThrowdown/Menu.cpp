//
//  Menu.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Menu.h"

using namespace std;

Menu::Menu(string title, vector<string> options, function<void(int)> callback, bool backButtonEnabled, int paginationLimit)
{
    this->title = title;
    this->options = options;
    this->callback = callback;
    this->backButtonEnabled = backButtonEnabled;
    this->paginationLimit = paginationLimit;
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

bool Menu::getBackButtonEnabled() const
{
    return backButtonEnabled;
}

int Menu::getPaginationLimit() const
{
    return paginationLimit;
}

void Menu::executeCallback(int argument)
{
    callback(argument);
}