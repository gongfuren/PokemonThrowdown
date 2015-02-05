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
    addChild(new TextLabelNode("Lv " + toString(statusBox.getLevel()) + " " + statusBox.getPokemonName() + " " + Pokemon::shortDescription(statusBox.getGender()) + " " + StatusBox::description(statusBox.getStatusToken()), this));
    const int Fullness = toInt(toDouble(HPBarWidth) * toDouble(statusBox.getHP()) / toDouble(statusBox.getHPTotal()));
    string bar = "HP:[";
    for (int i = 0; i < Fullness; i++)
    {
        bar += "%";
    }
    for (int i = Fullness; i < HPBarWidth; i++)
    {
        bar += " ";
    }
    bar += "]";
    if (statusBox.getHPVisible())
    {
        bar += " (" + toString(statusBox.getHP()) + "/" + toString(statusBox.getHPTotal()) + ")";
    }
    addChild(new TextLabelNode(bar, this));
}