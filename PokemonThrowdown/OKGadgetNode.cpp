//
//  OKGadgetNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "OKGadgetNode.h"
#include "utilities.h"

OKGadgetNode::OKGadgetNode(WinNode* parent)
: WinNode(parent)
{
}

void OKGadgetNode::display()
{
    WinNode::display();
    println("1: OK");
    getNumericalInput(1);
}
