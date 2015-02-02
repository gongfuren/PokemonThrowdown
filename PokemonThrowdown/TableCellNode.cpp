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
#include "Menu.h"

TableCellNode::TableCellNode(std::string label, int iD, WinNode* parent)
: WinNode(parent)
{
    this->iD = iD;
    addChild(new TextLabelNode(label, this));
}

BackTableCellNode::BackTableCellNode(WinNode* parent)
: TableCellNode(".. (Back)", Menu::BackValue, parent)
{
}

NextTableCellNode::NextTableCellNode(WinNode* parent)
: TableCellNode(">> (Next)", Menu::NextChoice, parent)
{
}

PrevTableCellNode::PrevTableCellNode(WinNode* parent)
: TableCellNode("<< (Prev)", Menu::PrevChoice, parent)
{
}