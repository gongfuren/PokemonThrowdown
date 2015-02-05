//
//  MenuNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__MenuNode__
#define __PokemonThrowdown__MenuNode__

#include <functional>
#include "WinNode.h"

#define function std::function
#define override virtual

class Menu;
class BannerNode;
class TableNode;
class NumericalGadgetNode;

//
// MenuNode
// Visual representation of a Menu.
// Master node for a option-based menu.
//
class MenuNode : public WinNode
{
public:
    MenuNode(const Menu& menu, WinNode* parent);
};

#undef function
#undef override

#endif /* defined(__PokemonThrowdown__MenuNode__) */
