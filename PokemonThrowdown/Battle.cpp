//
//  Battle.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Battle.h"
#include "Trainer.h"
#include "Menu.h"
#include "Window.h"
#include "Player.h"
#include "Dialogue.h"
#include "Action.h"
#include <vector>
#include "Team.h"
#include "StatusBox.h"
#include "Pokemon.h"
#include "Moves.h"
#include "Move.h"
#include "Stats.h"
#include "Stat.h"
#include "utilities.h"
#include "exceptions.h"
#include "Field.h"
#include "Slot.h"
#include "Computer.h"

using namespace std;

Battle::Battle(Window* window)
: Controller(window)
{
    Player* human = new Player(window);
    Computer* computer = new Computer(window);
    human->setOpponent(computer);
    computer->setOpponent(human);
    players.push_back(human);
    players.push_back(computer);
    turnsPassed = 0;
    victor = nullptr;
    field = new Field();
}

Battle::~Battle()
{
    for (Player* player : players)
    {
        delete player;
    }
}

void Battle::start()
{
    for (intro(); !isOver(); endOfTurn())
    {
        summonsPhase();
        actionPhase();
        battlePhase();
    }
}

void Battle::intro()
{
    for (vector<Player*>::reverse_iterator r = players.rbegin(); r != players.rend(); r++)
    {
        Player* player = *r;
        
        player->introduceSelf();
        player->initialSummon();
    }
}

void Battle::summonsPhase()
{
    // Replace fainted Pokemon
    for (Player* player : players)
    {
        if (player->getTrainer()->getTeam()->getSlot()->getPokemon() == nullptr)
        {
            player->selectReplacementPokemon();
        }
    }
}

void Battle::actionPhase()
{
    // Present current status box to the view
    getWindow()->present(Dialogue("Turn " + toString(turnsPassed+1)));
    
    int showHP = 0;
    for (vector<Player*>::reverse_iterator r = players.rbegin(); r != players.rend(); r++, showHP++)
    {
        Player* player = *r;
        
        getWindow()->present(StatusBox(player->getTrainer()->getTeam()->getSlot()->getPokemon(), toBool(showHP)));
    }

    // Prompt users for action
    for (Player* player : players)
    {
        player->selectAction();
    }
}

void Battle::battlePhase()
{
    vector<const Action*> actions;
    
    //
    // Pre-Battle Phase
    // Execute certain actions
    // Action::Bag: use item
    // Action::Run: set victor to opponent and return
    //
    for (const Player* player : players)
    {
        const Action* action = player->getAction();
        
        switch (action->type)
        {
            case Action::Switch:
            {
                const Trainer* trainer = player->getTrainer();
                const Pokemon* pokemon = trainer->getTeam()->getPokemon().at(Team::FirstSlot);
                
                getWindow()->present(Dialogue(trainer->getTitleAndName() + " withdrew " + pokemon->getFullName() + "!"));
            }
            case Action::Fight:
                actions.push_back(action);
                break;
            case Action::Bag:
                break;
            default: // Action::Run
                victor = player->getOpponent();
                return;
        }
    }
    
    // Process battle actions
    // Action::Fight, Action::Switch: sort actions
    sort(actions.begin(), actions.end(), Action::compare);
    
    //
    // Battle Phase
    // Execute battle actions
    // Action::Fight, Action::Switch: use attack or switch Pokemon
    //
    for (const Action* action : actions)
    {
        Pokemon* pokemon = action->pokemon;
        Move* move = action->move;
        const Trainer* trainer = pokemon->getTrainer();
        
        // TEMPORARY FIX (TODO)!!!
        if (action->type == Action::Fight && pokemon->getStats()->getHP()->getStatus() == 0)
        {
            continue;
        }
        
        switch (action->type)
        {
            case Action::Fight:
            {
                Dialogue moveDialogue = Dialogue(trainer->getTitleAndName() + "'s " + pokemon->getFullName() + " used " + move->getName() + "!");
                getWindow()->present(moveDialogue);
                action->move->execute();
            }
                break;
            case Action::Switch:
                getWindow()->present(Dialogue(trainer->getTitleAndName() + " sent out " + pokemon->getFullName() + "!"));
                trainer->getTeam()->setActive(action->pokemon);
                break;
            default:
                throw BattleControlFlowException("Attempt to execute non-Fight/non-Pokemon Action where a Fight/Pokemon Action was expected");
        }
    }
    
    // Check to see if someone won
    for (Player* player : players)
    {
        if (!player->getTrainer()->hasAblePokemon())
        {
            victor = player->getOpponent();
            return;
        }
    }
    
    //
    // Post Battle Phase
    // Deal with weather effects, status effects
    //
}

void Battle::endOfTurn()
{
    // Clear actions
    for (Player* player : players)
    {
        player->clearAction();
    }
    
    turnsPassed++;
}

bool Battle::isOver() const
{
    if (victor == nullptr)
    {
        return false;
    }
    else
    {
        getWindow()->present(Dialogue(victor->getTrainer()->getTitleAndName() + " won the battle!"));
        return true;
    }
}
