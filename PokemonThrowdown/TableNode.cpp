//
//  TableNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "TableNode.h"
#include "TableCellNode.h"

#define vector std::vector
#define string std::string

TableNode::TableNode(vector<string> labels, WinNode* parent)
: WinNode(parent)
{
    for (int i = 0; i < labels.size(); i++)
    {
        addChild(new TableCellNode(labels[i], i, this));
    }
}