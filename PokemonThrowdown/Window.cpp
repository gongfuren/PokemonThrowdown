//
//  Window.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Window.h"
#include "MenuNode.h"
#include "Alert.h"
#include "AlertNode.h"
#include "WindowView.h"

Window::Window()
{
    root = new WindowView(nullptr);
}

Window::~Window()
{
    delete root;
}

void Window::present(const Menu& menu)
{
    root->removeChildren();
    root->addChild(new MenuNode(menu, root));
}

void Window::alert(const Alert& alert)
{
    AlertNode alertNode = AlertNode(alert.getText(), nullptr);
    alertNode.display();
}

void Window::display()
{
    if (root != nullptr)
    {
        root->display();
    }
}