//
//  Game.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Game__
#define __PokemonThrowdown__Game__

class Settings;
class Guide;
class Window;

//
// Game
// The master controller for a PokemonThrowdown game.
//
class Game
{
public:
    Game();
    
    ~Game();
    
    void start();
    
private:
    Settings* settings;
    Guide* guide;
    Window* window;
};
#endif /* defined(__PokemonThrowdown__Game__) */
