//
//  DialogueNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/31/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__DialogueNode__
#define __PokemonThrowdown__DialogueNode__

#include "WinNode.h"
#include <iostream>

//
// DialogueNode
// A visual dialogue box containing text.
//
class DialogueNode : public WinNode
{
public:
    DialogueNode(std::string text, WinNode* parent);
};

#endif /* defined(__PokemonThrowdown__DialogueNode__) */
