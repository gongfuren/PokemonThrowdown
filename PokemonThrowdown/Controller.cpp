//
//  Controller.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/31/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Controller.h"
#include "Window.h"

Controller::Controller(Window* window)
{
    this->window = window;
}

Controller::~Controller()
{
}

Window* Controller::getWindow() const
{
    return window;
}