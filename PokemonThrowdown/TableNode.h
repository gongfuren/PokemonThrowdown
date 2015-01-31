//
//  TableNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__TableNode__
#define __PokemonThrowdown__TableNode__

#include "WinNode.h"
#include <vector>
#include <iostream>

//
// TableNode
// Represents a scrollable table view of items.
//
class TableNode : public WinNode
{
public:
    TableNode(std::vector<std::string> labels, WinNode* parent);
};

#endif /* defined(__PokemonThrowdown__TableNode__) */
