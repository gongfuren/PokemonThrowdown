//
//  MenuNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "MenuNode.h"
#include "TableNode.h"
#include "BannerNode.h"
#include "utilities.h" // toInt()
#include "Menu.h"

MenuNode::MenuNode(const Menu& menu, WinNode* parent)
: WinNode(parent)
{
    addChild(new BannerNode(menu.getTitle(), this));
    addChild(new TableNode(menu.getOptions(), menu.getPaginationLimit(), menu.getBackButtonEnabled(), menu.getCallback(), this));
}