//
//  StatusBoxNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/1/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__StatusBoxNode__
#define __PokemonThrowdown__StatusBoxNode__

#include "WinNode.h"

class StatusBox;

class StatusBoxNode : public WinNode
{
public:
    StatusBoxNode(const StatusBox& statusBox, WinNode* parent);
    
private:
};

#endif /* defined(__PokemonThrowdown__StatusBoxNode__) */
