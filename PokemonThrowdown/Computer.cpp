//
//  Computer.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Computer.h"
#include "Window.h" 
#include "Trainer.h" 
#include "Team.h" 
#include "Slot.h" 
#include "Pokemon.h"
#include "Moves.h"
#include "Move.h"
#include "Stats.h"
#include "utilities.h"
#include "Stat.h" 
#include "Action.h"

Computer::Computer(Window* window)
: Player(window)
{
}

Computer::~Computer()
{
}

void Computer::introduceSelf() const
{
    getWindow()->present(Dialogue(trainer->getTitleAndName() + " would like to battle!"));
}

void Computer::initialSummon()
{
    const Pokemon* pokemon = trainer->getTeam()->getSlot()->getPokemon();
    
    getWindow()->present(Dialogue(trainer->getTitleAndName() + " sent out " + pokemon->getFullName() + "!"));
}

void Computer::selectAction()
{
    const Team* team = trainer->getTeam();
    const Moves* moves = team->getSlot()->getPokemon()->getMoves();
    const int MoveNumber = randInt(0, moves->getNumber()-1);
    Move* move = moves->getMoves().at(MoveNumber);
    Slot* target = getOpponent()->getTrainer()->getTeam()->getSlot();
    
    move->setTarget(target);
    action = new Action(moves->getMoves().at(MoveNumber), team->getSlot()->getPokemon());
}

void Computer::selectReplacementPokemon()
{
    for (;;)
    {
        const Team* team = trainer->getTeam();
        const int choice = randInt(1, toInt(team->getPokemon().size())-1);
        
        Pokemon* pokemon = trainer->getTeam()->getPokemon().at(choice);
        
        // TEMP fix (TODO)!!!
        if (pokemon->getStats()->getHP()->getStatus() == 0)
        {
            continue;
        }
        
        getWindow()->present(Dialogue(trainer->getTitleAndName() + " sent out " + pokemon->getFullName() + "!"));
        trainer->getTeam()->setActive(pokemon);
        break;
    }
}