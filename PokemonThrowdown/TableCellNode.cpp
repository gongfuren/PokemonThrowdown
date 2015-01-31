//
//  TableCellNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "TableCellNode.h"
#include "TextLabelNode.h"
#include "utilities.h" // print()

TableCellNode::TableCellNode(std::string label, int iD, WinNode* parent)
: WinNode(parent)
{
    this->iD = iD;
    addChild(new TextLabelNode(label, this));
}

void TableCellNode::display()
{
    print(iD+1);
    print(": ");
    WinNode::display();
}