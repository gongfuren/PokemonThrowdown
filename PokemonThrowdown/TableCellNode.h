//
//  TableCellNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__TableCellNode__
#define __PokemonThrowdown__TableCellNode__

#include "WinNode.h"
#include <iostream>

#define override virtual

//
// TableCellNode
// Represents one cell or one option of a table list.
//
class TableCellNode : public WinNode
{
public:
    TableCellNode(std::string label, int iD, WinNode* parent);
    
protected:
    int iD;
};

class BackTableCellNode : public TableCellNode
{
public:
    BackTableCellNode(WinNode* parent);
};

class NextTableCellNode : public TableCellNode
{
public:
    NextTableCellNode(WinNode* parent);
};

class PrevTableCellNode : public TableCellNode
{
public:
    PrevTableCellNode(WinNode* parent);
};

#undef override

#endif /* defined(__PokemonThrowdown__TableCellNode__) */
