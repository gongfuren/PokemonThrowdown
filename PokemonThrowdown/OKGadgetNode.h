//
//  OKGadgetNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__OKGadgetNode__
#define __PokemonThrowdown__OKGadgetNode__

#include "WinNode.h"

#define override virtual

//
// OKGadgetNode
// Represents a UI "OK" button. When this object is displayed, it will halt
// the program to grab input from the terminal.
//
class OKGadgetNode : public WinNode
{
public:
    OKGadgetNode(WinNode* parent);
    
    override void display();
    
private:
};

#undef override

#endif /* defined(__PokemonThrowdown__OKGadgetNode__) */
