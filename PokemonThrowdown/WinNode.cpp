//
//  WinNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "WinNode.h"
#include <algorithm> // find()

#define vector std::vector

WinNode::WinNode(WinNode* parent)
{
    this->parent = parent;
}

WinNode::~WinNode()
{
    for (WinNode* node : children)
    {
        delete node;
    }
}

vector<WinNode*> WinNode::getChildren() const
{
    return children;
}

void WinNode::addChild(WinNode* child)
{
    children.push_back(child);
}

void WinNode::removeFromParent()
{
    if (parent != nullptr)
    {
        parent->children.erase(find(parent->children.begin(), parent->children.end(), this));
    }
}

void WinNode::removeChildren()
{
    for (WinNode* node : children)
    {
        delete node;
    }
    
    children.clear();
}

void WinNode::display()
{
    for (WinNode* node : children)
    {
        node->display();
    }
}