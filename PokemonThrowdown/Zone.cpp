//
//  Zone.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/16/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Zone.h"

Zone::Zone(int X, int Y, int width, int height)
{
    m_X = X;
    m_Y = Y;
    m_width = width;
    m_height = height;
}

int Zone::getWidth() const
{
    return m_width;
}

int Zone::getHeight() const
{
    return m_height;
}

int Zone::getXPosition() const
{
    return m_X;
}

int Zone::getYPosition() const
{
    return m_Y;
}