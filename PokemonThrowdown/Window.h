//
//  Window.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Window__
#define __PokemonThrowdown__Window__

#include "Dialogue.h"

class Menu;
class WinNode;
class Alert;
class Dialogue;
class StatusBox;

//
// Window
// Controls output to the terminal.
// Controls a WindowView, which itself controls a hierarchy of view nodes.
//
class Window
{
public:
    Window();
    
    ~Window();
    
    void clear();
    
    void present(const Menu& menu);
    
    void alert(const Alert& alert);
    
    void present(const Dialogue& dialogue);
    
    void present(const StatusBox& statusBox);
    
private:
    WinNode* root;
};

#endif /* defined(__PokemonThrowdown__Window__) */
