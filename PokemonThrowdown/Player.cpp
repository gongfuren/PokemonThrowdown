//
//  Player.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/10/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Player.h"
#include "Battle.h"
#include "constants.h"
#include "strings.h"

#include <iostream>
#include <sstream>
using namespace std;

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

Player::Player(TrainerData h, Battle* battle)
: Trainer(h, battle)
{
    
}

Player::~Player()
{
    
}

void Player::actionSelect()
{
    if (!canChooseAction())
        return;
    
    Battle* battle = getBattle();
    bool rerun = false;
    
    do
    {
        cout << "What would you like to do?" << endl;
        
        cout << "1: " << "Fight" << "!" << endl
        << "2: " << "Bag" << endl
        << "3: " << "Pokemon" << endl
        << "4: " << "Run" << endl;
        
        int choice;
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                rerun = !chooseFight();
                break;
            case 2:
                rerun = !chooseBag();
                break;
            case 3:
                rerun = !choosePokemon();
                break;
            case 4:
                rerun = !chooseRun();
                break;
            default:
                break;
        }
    }
    while (rerun);
    
    battle->summonEffects();
}

bool Player::chooseRun()
{
    cout << "Are you sure you'd like to run and forfeit the match?" << endl;
    
    cout << "1: " << "Yes" << endl << "2: " << "No" << endl;
    
    int choice;
    cin >> choice;
    
    switch (choice)
    {
        case 1:
            cout << getTitleName() << " " << "has forfeited the match."
            << endl;
            getBattle()->getOpponent()->setVictory();
            setIntendedMove(RunDecision);
            return true;
        default:
            return false;
    }
}

bool Player::choosePokemon()
{
    return trainerSummon(true);
}

bool Player::isComputer() const
{
    return false;
}

bool Player::trainerSummon(bool optional)
{
    int choice, i;
    bool rerun = false;
    Pokemon* pokemon;
    
    do
    {
        rerun = false;
        
        cout << "Choose a Pokemon" << ":" << endl;
        
        cout << generateBalls() << endl;
        
        // Summon prompt
        for (i = 0; i < MAXPOKEMON; i++)
        {
            pokemon = getPokemon(i);
            
            if (pokemon == NULL)
                break;
            
            ostringstream oss;
            
            if (pokemon->getStatus() != HealthyStatus)
                oss << ": " << getBattle()->statusText(pokemon, false);
            
            if (getCurrent() == i && !pokemon->isFainted())
                oss << ": " << "In Battle";
            
            if (pokemon != NULL)
                cout << i+1 << ": " << pokemon->getName() << oss.str() << endl;
        }
        
        if (optional)
            cout << ++i << ": (" << "Back" << ")" << endl;
        
        cin >> choice;
        
        if (choice > 0 && choice <= i)
        {
            if (optional && choice == i)
                return false;
        }
        else
        {
            rerun = true;
            continue;
        }
        
        // Useful?
        if (getPokemon(choice-1) == NULL)
        {
            rerun = true;
            continue;
        }
        
        int choicee;
        bool rerunn = false;
        
        do
        {
            rerunn = false;
            rerun = false;
            
            cout << "What to do with" << " " << getPokemon(choice-1)->getName()
            << "?" << endl << "1: " << "Switch" << endl << "2: "
            << "Summary" << endl << "3: " << "Check Moves" << endl
            << "4: (" << "Back" << ")" << endl;
            
            cin >> choicee;
            
            switch (choicee)
            {
                default:
                    rerunn = true;
                    continue;
                case 1:
                    if (getPokemon(choice-1)->isFainted())
                    {
                        cout << getPokemon(choice-1)->getName() << " "
                        << "is fainted and cannot battle." << endl;
                        rerunn = true;
                    }
                    else if (getCurrent() == choice-1)
                    {
                        cout << getPokemon(choice-1)->getName() << " "
                        << "is already out!" << endl;
                        rerunn = true;
                    }
                    break;
                case 2:
                    getBattle()->dispPokeSummary(choice-1);
                    rerunn = true;
                    break;
                case 3:
                    getBattle()->dispPokeMoves(choice-1);
                    rerunn = true;
                    break;
                case 4:
                    rerun = true;
                    rerunn = false;
                    break;
            }
            
        } while (rerunn);
        
    }
    while (rerun);
    
    // Set intended switch
    setIntendedSwitch(choice-1);
    setIntendedMove(SwitchDecision);
    
    return true;
}

bool Player::chooseFight()
{
    Pokemon* pokemon = getPokemon();
    
    int playerChoice, j;
    bool canMega, willMegaEvolve = false;
    
    do
    {
        cout << "Choose a move" << ":" << endl;
        
        for (j = 0; j < MAXMOVES; j++)
        {
            cout << j+1 << ": ";
            
            cout << getPokemonMove(j)->getName() << endl;
        }
        
        canMega = pokemon->canMegaEvolve();
        
        if (canMega)
        {
            cout << ++j << ": " << "*Mega Evolution*";
            
            if (willMegaEvolve)
                cout << " (" << "Selected" << ")";
            
            cout << endl;
        }
        
        cout << ++j << ": (" << "Move Info" << ")" << endl;
        cout << ++j << ": (" << "Back" << ")" << endl;
        
        cin >> playerChoice;
        
        if (playerChoice == j-1)
            getBattle()->dispPokeMoves();
        
        if (canMega && playerChoice == 5)
        {
            if (willMegaEvolve)
            {
                willMegaEvolve = false;
            }
            else
            {
                willMegaEvolve = true;
            }
            
            playerChoice = j-1;
        }
        
    } while (playerChoice == j-1);
    
    switch (playerChoice)
    {
        default:
            return false;
        case 1:
        case 2:
        case 3:
        case 4:
            if (!willMegaEvolve)
                setIntendedMove(FightDecision, playerChoice-1);
            else
                setIntendedMove(MegaDecision, playerChoice-1);
            break;
    }
    
    return true;
}
