//
//  Player.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/31/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Player__
#define __PokemonThrowdown__Player__

#include "Controller.h"

#define vector std::vector
#define override virtual

class Window;
class Trainer;
struct Action;

class Player : public Controller
{
public:
    Player(Window* window);
    
    virtual ~Player();
    
    virtual void initialSummon();
    
    virtual void selectAction();
    
    bool didForfeit() const;
    
    Trainer* getTrainer() const;
    
    Action* getAction() const;
    
    void clearAction();
        
protected:
    Trainer* trainer;
    Action* action;
};

class Computer : public Player
{
public:
    Computer(Window* window);
    
    ~Computer();
    
    override void initialSummon();
    
    void introduceSelf() const;
    
    override void selectAction();
};

#undef vector
#undef override

#endif /* defined(__PokemonThrowdown__Player__) */
