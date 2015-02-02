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
#include "Dialogue.h"
#include "DialogueNode.h"
#include "StatusBoxNode.h"

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
    root->display();
}

void Window::alert(const Alert& alert)
{
    AlertNode alertNode = AlertNode(alert.getText(), nullptr);
    alertNode.display();
}

void Window::present(const Dialogue& dialogue)
{
    root->removeChildren();
    root->addChild(new DialogueNode(dialogue.getText(), nullptr));
    root->display();
}

void Window::present(const StatusBox& statusBox)
{
    root->removeChildren();
    root->addChild(new StatusBoxNode(statusBox, nullptr));
    root->display();
}