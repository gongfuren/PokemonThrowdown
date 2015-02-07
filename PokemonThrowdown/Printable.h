//
//  Printable.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Printable__
#define __PokemonThrowdown__Printable__

#include <string> 

#define string std::string

//
// Printable
// Interface for a printable type.
//
class Printable
{
public:
    //
    // description()
    // Returns a string representation of the object
    //
    virtual string description() const = 0;
};

#undef string

#endif /* defined(__PokemonThrowdown__Printable__) */
