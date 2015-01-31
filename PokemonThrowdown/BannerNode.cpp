//
//  BannerNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "BannerNode.h"
#include "TextLabelNode.h"

BannerNode::BannerNode(std::string label, WinNode* parent)
: WinNode(parent)
{
    addChild(new TextLabelNode(label, this));
}