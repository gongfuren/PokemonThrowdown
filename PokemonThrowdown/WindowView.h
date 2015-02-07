//
//  WindowView.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__WindowView__
#define __PokemonThrowdown__WindowView__

#include "WinNode.h"

//
// WindowView
// WinNode managing the entire window for terminal.
//
class WindowView : public WinNode
{
public:
    WindowView();
    WindowView(WinNode* parent);
};

#endif /* defined(__PokemonThrowdown__WindowView__) */
