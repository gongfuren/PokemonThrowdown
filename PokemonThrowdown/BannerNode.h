//
//  BannerNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__BannerNode__
#define __PokemonThrowdown__BannerNode__

#include "WinNode.h"
#include <iostream>

//
// BannerNode
// Represents a banner to be displayed at the top of a Menu.
//
class BannerNode : public WinNode
{
public:
    BannerNode(std::string label, WinNode* parent);
};

#endif /* defined(__PokemonThrowdown__BannerNode__) */
