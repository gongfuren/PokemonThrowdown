//
//  Player.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/31/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include <vector>
#include "Player.h"
#include "Trainer.h"
#include "Window.h"
#include "Dialogue.h"
#include "Team.h"
#include "Pokemon.h"
#include "Menu.h"
#include "Dialogue.h"
#include "Alert.h"
#include "Moves.h"
#include "Move.h"
#include "Action.h"
#include "utilities.h" // randInt

using namespace std;

Player::Player(Window* window)
: Controller(window)
{
    trainer = new Trainer();
    action = nullptr;
}

Player::~Player()
{
    delete trainer;
}

void Player::initialSummon()
{
    getWindow()->present(Dialogue("You sent out " + trainer->getTeam()->getActive()[0]->getFullName() + "!"));
}

void Player::selectAction()
{
    int choice = 0;
    
    while (action == nullptr)
    {
        Menu menu = Menu("What would you like to do?", { "Fight!", "Bag", "Pokemon", "Run" }, [&choice] (int a) { choice = a; });
        getWindow()->present(menu);
        
        switch (choice)
        {
            case 0:
            {
                Menu moveSelect = Menu("Choose a move:", trainer->getTeam()->getActive()[Team::FirstActiveSlot]->getMoves()->getMoveNames(), [&choice] (int a) { choice = a; }, true);
                getWindow()->present(moveSelect);
                
                switch (choice)
                {
                    default:
                        action = new Action(Action::Fight, choice);
                        break;
                    case Menu::BackValue:
                        break;
                }
            }
                break;
            case 1:
                getWindow()->alert(Alert("You can't do that right now."));
                break;
            case 2:
            {
                Menu pokemonSelect = Menu("Choose a Pokemon:", trainer->getTeam()->getPokemonNames(), [&choice] (int a) { choice = a; }, true);
                getWindow()->present(pokemonSelect);
                
                switch (choice)
                {
                    default:
                        action = new Action(Action::Pokemon, choice);
                        break;
                    case Menu::BackValue:
                        break;
                }
            }
                break;
            default:
            {
                Menu runSelect = Menu("Are you sure you want to run and forfeit the match?", { "Yes", "No" }, [&choice] (int a) { choice = a; });
                getWindow()->present(runSelect);
                
                if (choice == 0)
                {
                    action = new Action(Action::Run, Action::DontCare);
                    getWindow()->present(Dialogue("You forfeited the match."));
                }
            }
                break;
        }
    }
}

Trainer* Player::getTrainer() const
{
    return trainer;
}

Action* Player::getAction() const
{
    return action;
}

void Player::clearAction()
{
    delete action;
    action = nullptr;
}

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
    getWindow()->present(Dialogue(trainer->getTitleAndName() + " sent out " + trainer->getTeam()->getActive()[Team::FirstActiveSlot]->getFullName() + "!"));
}

void Computer::selectAction()
{
    const int MoveNumber = randInt(0, trainer->getTeam()->getActive()[Team::FirstActiveSlot]->getMoves()->getNumber()-1);
    
    action = new Action(Action::Fight, MoveNumber);
}