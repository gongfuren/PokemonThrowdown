//
//  TextLabelNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "TextLabelNode.h"
#include "utilities.h"

TextLabelNode::TextLabelNode(std::string label, WinNode* parent)
: WinNode(parent)
{
    this->label = label;
}

void TextLabelNode::display()
{
    println(label);
    WinNode::display();
}