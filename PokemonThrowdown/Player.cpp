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
#include "utilities.h" // randInt()
#include "Slot.h"
#include "Stats.h"
#include "Stat.h"

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
    getWindow()->present(Dialogue("You sent out " + trainer->getTeam()->getSlot()->getPokemon()->getFullName() + "!"));
}

void Player::introduceSelf() const
{
}

void Player::selectAction()
{
    int choice = Action::DontCare;
    
    while (action == nullptr)
    {
        Menu menu = Menu("What will " + trainer->getTeam()->getSlot()->getPokemon()->getFullName() + " do?", { "Fight!", "Bag", "Pokemon", "Run" }, [&choice] (int a) { choice = a; });
        getWindow()->present(menu);
        
        switch (choice)
        {
            case 0:
            {
                const Team* team = trainer->getTeam();
                const Pokemon* pokemon = team->getSlot()->getPokemon();
                const Moves* moves = pokemon->getMoves();
                
                const Menu moveSelect = Menu("Choose a move:", moves->getMoveNames(), [&choice] (int a) { choice = a; }, true);
                getWindow()->present(moveSelect);
                
                switch (choice)
                {
                    default:
                    {
                        Move* move = moves->getMoves().at(choice);
                        Slot* target = getOpponent()->getTrainer()->getTeam()->getSlot();
                        
                        move->setTarget(target);
                        action = new Action(move, team->getSlot()->getPokemon());
                    }
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
                const Team* team = trainer->getTeam();
                Menu pokemonSelect = Menu("Choose a Pokemon:", team->getPokemonNamesWithStatus(), [&choice] (int a) { choice = a; }, true);
                getWindow()->present(pokemonSelect);
                
                switch (choice)
                {
                    default:
                        action = new Action(team->getPokemon().at(choice));
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
                    action = new Action();
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

void Player::setOpponent(Player *opponent)
{
    this->opponent = opponent;
}

Player* Player::getOpponent() const
{
    return opponent;
}

void Player::selectReplacementPokemon()
{
    for (;;)
    {
        int choice;
        const Team* team = trainer->getTeam();
        
        Menu pokemonSelect = Menu("Choose a Pokemon:", team->getPokemonNamesWithStatus(), [&choice] (int a) { choice = a; });
        getWindow()->present(pokemonSelect);
        
        Pokemon* pokemon = trainer->getTeam()->getPokemon().at(choice);
        
        if (pokemon->getStats()->getHP()->getStatus() == 0)
        {
            getWindow()->alert(Alert(pokemon->getFullName() + " is fainted and cannot battle."));
            continue;
        }
        
        getWindow()->present(Dialogue(trainer->getTitleAndName() + " sent out " + pokemon->getFullName() + "!"));
        trainer->getTeam()->setActive(pokemon);
        break;
    }
}