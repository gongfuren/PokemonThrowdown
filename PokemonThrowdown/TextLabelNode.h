//
//  TextLabelNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__TextLabelNode__
#define __PokemonThrowdown__TextLabelNode__

#include "WinNode.h"
#include <iostream>

#define override virtual

//
// TextLabelNode
// Represents textual information within a view.
//
class TextLabelNode : public WinNode
{
public:
    TextLabelNode(std::string label, WinNode* parent);
    
    override void display();
    
private:
    std::string label;
};

#undef override

#endif /* defined(__PokemonThrowdown__TextLabelNode__) */
