//
//  AlertNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "AlertNode.h"
#include "TextLabelNode.h"
#include "OKGadgetNode.h"
#include "utilities.h" // println()

AlertNode::AlertNode(std::string alert, WinNode* parent)
: WinNode(parent)
{
    addChild(new TextLabelNode(alert, this));
    addChild(new OKGadgetNode(this));
}