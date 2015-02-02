//
//  Game.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Game.h"
#include "Menu.h"
#include "Window.h"
#include "utilities.h" // println()
#include "Battle.h"
#include "Settings.h"
#include "Guide.h"
#include "Alert.h"
#include <iostream>

Game::Game()
{
    settings = new Settings();
    guide = new Guide();
    window = new Window();
}

Game::~Game()
{
    delete settings;
    delete guide;
    delete window;
}

void Game::start()
{
    Menu titleScreen = Menu(" (                                                 \n )\\ )       )                                      \n(()/(    ( /(   (    )                             \n /(_))(  )\()) ))\\  (     (   (                    \n(_))  )\((_)\\ /((_) )\\  ' )\\  )\\ )                 \n| _ \((_) |(_|_)) _((_)) ((_)_(_/(                 \n|  _/ _ \\ / // -_) '  \() _ \\ ' \\))                \n|_|*\\__)/_\\)\\___|_|_|_|\\___/(||_|                 \n ` )  /(( /( (       (  (    )\\ )    (  (          \n  ( )(_))\()))(   (  )\\))(  (()/( (  )\\))(   (     \n (_(_()|(_)\(()\\  )\((_)()\\  ((_)))\((_)()\\  )\\ )  \n |_   _| |(_)((_)((_)(()((_) _| |((_)(()((_)_(_/(  \n   | | | ' \\| '_/ _ \\ V  V / _` / _ \\ V  V / ' \\)) \n   |_| |_||_|_| \\___/\\_/\\_/\\__,_\\___/\\_/\\_/|_||_|  \n                                            v0.6\nPress START to begin!", { "START" }, [] (int a) {});
    window->present(titleScreen);
    
    int choice = 0;
    
    while (choice != 3)
    {
        Menu mainMenu = Menu("O***0***O***0***O***0\n* Pokemon Throwdown * v0.6\n0***O***0***O***0***O", { "Play!", "Settings", "Guide", "Quit" }, [&choice] (int a) { choice = a; });
        window->present(mainMenu);
        
        switch (choice)
        {
            case 0:
            {
                Battle b(window);
                b.start();
            }
                break;
            case 1:
            case 2:
                window->alert(Alert("Coming soon!"));
                break;
            default:
                break;
        }
    }
}