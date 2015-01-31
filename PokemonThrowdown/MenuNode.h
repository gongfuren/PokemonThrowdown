//
//  MenuNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__MenuNode__
#define __PokemonThrowdown__MenuNode__

#include "WinNode.h"
#include "Menu.h"

//
// MenuNode
// Master node for a option-based menu.
//
class MenuNode : public WinNode
{
public:
    MenuNode(const Menu& menu, WinNode* parent);
};

#endif /* defined(__PokemonThrowdown__MenuNode__) */
