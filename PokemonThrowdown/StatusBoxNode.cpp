//
//  StatusBoxNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/1/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "StatusBoxNode.h"
#include "TextLabelNode.h"
#include "StatusBox.h"
#include "utilities.h"
#include <iostream> 
#include "Pokemon.h"

using namespace std;

StatusBoxNode::StatusBoxNode(const StatusBox& statusBox, WinNode* parent)
: WinNode(parent)
{
    addChild(new TextLabelNode("Lv " + toString(statusBox.getLevel()) + " " + statusBox.getPokemonName() + " " + Pokemon::description(statusBox.getGender()) + " " + toString(statusBox.getStatusToken()) + " OOO", this));
}