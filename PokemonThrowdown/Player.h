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

//
// Player
// A human player that controls a Trainer and their Pokemon.
//
class Player : public Controller
{
public:
    Player(Window* window);
    
    virtual ~Player();
    
    virtual void initialSummon();
    
    virtual void introduceSelf() const;
    
    virtual void selectAction();
    
    Trainer* getTrainer() const;
    
    Action* getAction() const;
    
    void clearAction();
    
    void setOpponent(Player* opponent);
    
    Player* getOpponent() const;
    
    virtual void selectReplacementPokemon();
        
protected:
    Trainer* trainer;
    Action* action;
    Player* opponent;
};

//
// Computer
// A Player that selects its own actions instead of prompting the user to select
// its actions.
//
class Computer : public Player
{
public:
    Computer(Window* window);
    
    ~Computer();
    
    override void initialSummon();
    
    override void introduceSelf() const;
    
    override void selectAction();
    
    override void selectReplacementPokemon();
};

#undef vector
#undef override

#endif /* defined(__PokemonThrowdown__Player__) */
