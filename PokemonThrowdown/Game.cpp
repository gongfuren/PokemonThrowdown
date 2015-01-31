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

Game::Game()
{
    window = new Window();
    battle = new Battle(window);
    settings = new Settings();
    guide = new Guide();
}

Game::~Game()
{
    delete battle;
    delete settings;
    delete guide;
    delete window;
}

void Game::start()
{
    Menu titleScreen = Menu(" (                                                 \n )\\ )       )                                      \n(()/(    ( /(   (    )                             \n /(_))(  )\()) ))\\  (     (   (                    \n(_))  )\((_)\\ /((_) )\\  ' )\\  )\\ )                 \n| _ \((_) |(_|_)) _((_)) ((_)_(_/(                 \n|  _/ _ \\ / // -_) '  \() _ \\ ' \\))                \n|_|*\\__)/_\\)\\___|_|_|_|\\___/(||_|                 \n ` )  /(( /( (       (  (    )\\ )    (  (          \n  ( )(_))\()))(   (  )\\))(  (()/( (  )\\))(   (     \n (_(_()|(_)\(()\\  )\((_)()\\  ((_)))\((_)()\\  )\\ )  \n |_   _| |(_)((_)((_)(()((_) _| |((_)(()((_)_(_/(  \n   | | | ' \\| '_/ _ \\ V  V / _` / _ \\ V  V / ' \\)) \n   |_| |_||_|_| \\___/\\_/\\_/\\__,_\\___/\\_/\\_/|_||_|  \n                                            v0.6\nPress START to begin!", { "START" }, [] (int a) {});
    window->present(titleScreen);
    window->display();
    
    bool userSelectedQuitGame = false;
    
    while (!userSelectedQuitGame)
    {
        Menu mainMenu = Menu("O***0***O***0***O***0\n* Pokemon Throwdown * v0.6\n0***O***0***O***0***O", { "Play!", "Settings", "Guide", "Quit" },
                             [&] (int a)
                             {
                                 switch (a)
                                 {
                                     case 1:
                                         battle->start();
                                         break;
                                     case 2:
                                     case 3:
                                         window->alert(Alert("Coming soon!"));
                                         break;
                                     default:
                                         userSelectedQuitGame = true;
                                         break;
                                 }
                             }
                             );
        window->present(mainMenu);
        window->display();
    }
}