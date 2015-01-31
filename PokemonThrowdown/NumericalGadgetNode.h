//
//  NumericalGadgetNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__NumericalGadgetNode__
#define __PokemonThrowdown__NumericalGadgetNode__

#include "WinNode.h"
#include <functional> // std::function

#define override virtual

//
// NumericalGadgetNode
// Represents an input prompt where the program is expecting a number. When
// this object is displayed, it will halt the program to grab input from the
// terminal.
//

class NumericalGadgetNode : public WinNode
{
public:
    NumericalGadgetNode(int range, std::function<void(int)> callback, WinNode* parent);

    override void display();
    
private:
    int range;
    std::function<void(int)> callback;
};

#undef override

#endif /* defined(__PokemonThrowdown__NumericalGadgetNode__) */
