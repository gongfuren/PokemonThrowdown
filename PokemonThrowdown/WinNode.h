//
//  WinNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__WinNode__
#define __PokemonThrowdown__WinNode__

#include <vector>

class Window;

//
// WinNode
// Base class for window view nodes. Calling display() on one will call display()
// on all of a node's children.
//
class WinNode
{
public:
    WinNode(WinNode* parent);
    
    virtual ~WinNode();
    
    std::vector<WinNode*> getChildren() const;
    
    void addChild(WinNode* child);
    
    void removeFromParent();
    
    void removeChildren();
    
    virtual void display();
    
private:
    std::vector<WinNode*> children;
    WinNode* parent;
};

#endif /* defined(__PokemonThrowdown__WinNode__) */
