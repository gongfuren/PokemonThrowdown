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

using namespace std;

Battle::Battle(Window* window)
: Controller(window)
{
    human = new Player(window);
    computer = new Computer(window);
    players.push_back(human);
    players.push_back(computer);
    turnsPassed = 0;
    victor = nullptr;
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
        actionPhase();
        battlePhase();
    }
}

void Battle::intro()
{
    computer->introduceSelf();
    computer->initialSummon();
    human->initialSummon();
}

void Battle::actionPhase()
{
    vector<Player*> p = vector<Player*> { computer, human };
    
    for (Player* player : p)
    {
        getWindow()->present(StatusBox(player->getTrainer()->getTeam()->getActive()[Team::FirstActiveSlot]));
    }
    
    for (Player* player : players)
    {
        player->selectAction();
    }
}

void Battle::battlePhase()
{
    for (Player* player : players)
    {
        if (player->getAction()->type == Action::Run)
        {
            if (player == human)
            {
                victor = computer;
            }
            else
            {
                victor = human;
            }
            return;
        }
    }
}

void Battle::endOfTurn()
{
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