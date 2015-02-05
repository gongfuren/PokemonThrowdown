//
//  Battle.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Battle__
#define __PokemonThrowdown__Battle__

#include <vector> 
#include "Controller.h"

class Player;
class Window;
class Computer;
class Field;

//
// Battle
// Orchestrates Trainers and battle phases.
//
class Battle : public Controller
{
public:
    Battle(Window* window);
    
    ~Battle();
    
    void start();
    
    void intro();
    
    void summonsPhase();
    
    void actionPhase();
    
    void battlePhase();
    
    void endOfTurn();
    
    bool isOver() const;
    
private:
    std::vector<Player*> players;
    Player* victor;
    int turnsPassed;
    Field* field;
};

#endif /* defined(__PokemonThrowdown__Battle__) */
