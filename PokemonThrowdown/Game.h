//
//  Game.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 9/6/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Game__
#define __PokemonThrowdown__Game__

#include "utilities.h"
#include "Settings.h"

class Game
{
public:
    // Begin the Game
    Game()
    {
        start();
    };
    void start()
    {
        titleScreen();
        loadingScreen();
        mainMenu();
    };
    
    // Accessor (get) functions
    Settings* getSettings()
    {
        return &m_settings;
    };
    
private:
    // Core functions
    void titleScreen();
    void loadingScreen();
    void mainMenu();
    
    // Helper functions
    void startBattle();
    void guideBook();
    
    // Secondary functions
    void displayTypes();
    void displayCredits();
    void displayHelp();
    
    void typeSummary(int whichType = 0);
    void printTitle(int whichTitle = randInt(0, 2));
    void pokeMoveDex(bool moves = false);
    void pokeMoveDexBrowse(bool moves);
    void pokeMoveDexRandom(bool moves);
    void pokeMoveDexSearch(bool moves);
    
    // Data members
    Settings m_settings;
};

#endif /* defined(__PokemonThrowdown__Game__) */