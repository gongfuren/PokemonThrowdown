//
//  NumericalGadgetNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "NumericalGadgetNode.h"
#include "utilities.h"

NumericalGadgetNode::NumericalGadgetNode(int range, std::function<void(int)> callback, WinNode* parent)
: WinNode(parent)
{
    this->range = range;
    this->callback = callback;
}

void NumericalGadgetNode::display()
{
    WinNode::display();
    callback(getNumericalInput(range));
}