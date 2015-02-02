//
//  DialogueNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/31/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "DialogueNode.h"
#include "TextLabelNode.h"
#include "OKGadgetNode.h"

using namespace std;

DialogueNode::DialogueNode(string text, WinNode* parent)
: WinNode(parent)
{
    addChild(new TextLabelNode(text, this));
}