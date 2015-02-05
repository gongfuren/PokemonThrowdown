//
//  Dialogue.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/31/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Dialogue__
#define __PokemonThrowdown__Dialogue__

#include <iostream>
#include "Presentable.h"

//
// Dialogue
// A dialogue to be presented to the user in the standard dialogue box.
//
class Dialogue : public Presentable
{
public:
    Dialogue(std::string text);
    
    std::string getText() const;
    
private:
    std::string text;
};

class Question : public Dialogue
{
public:
    Question(std::string text);
};

#endif /* defined(__PokemonThrowdown__Dialogue__) */
