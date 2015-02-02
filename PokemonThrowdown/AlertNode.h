//
//  AlertNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__AlertNode__
#define __PokemonThrowdown__AlertNode__

#include "WinNode.h"
#include <iostream>

#define override virtual

//
// AlertNode
// Intended for a short-lived alert. Passed in to Window and immediately
// executed.
//
class AlertNode : public WinNode
{
public:
    AlertNode(std::string alert, WinNode* parent);
        
private:
};

#undef override

#endif /* defined(__PokemonThrowdown__AlertNode__) */
