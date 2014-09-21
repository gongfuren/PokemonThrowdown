//
//  Zone.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 7/16/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Zone__
#define __PokemonThrowdown__Zone__

#include <iostream>

// Vastly unfinished

class Zone
// Abstract class representing any "Zone" on the battlefield that has
// its own characteristics and may or may not hold a/some Pokemon at any given
// time
{
public:
    // Accessor functions
    int getWidth() const;
    int getHeight() const;
    int getXPosition() const;
    int getYPosition() const;
    
    Zone(int X, int Y, int width, int height);
    
private:
    int m_width;
    int m_height;
    int m_X;
    int m_Y;
};

#endif /* defined(__PokemonThrowdown__Zone__) */
