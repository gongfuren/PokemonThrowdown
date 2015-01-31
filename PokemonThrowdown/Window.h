//
//  Window.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Window__
#define __PokemonThrowdown__Window__

class Menu;
class WinNode;
class Alert;

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
    
    void display();
    
private:
    WinNode* root;
};

#endif /* defined(__PokemonThrowdown__Window__) */
