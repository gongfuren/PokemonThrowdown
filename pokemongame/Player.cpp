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
        cout << bFStrings[53] << endl;
        
        cout << "1: " << bFStrings[54] << endl
        << "2: " << bFStrings[55] << endl
        << "3: " << bFStrings[21] << endl
        << "4: " << bFStrings[56] << endl;
        
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
    cout << bFStrings[57] << endl;
    
    cout << "1: " << bFStrings[58] << endl << "2: " << bFStrings[59] << endl;
    
    int choice;
    cin >> choice;
    
    switch (choice)
    {
        case 1:
            cout << getTitle() << " " << getName() << " " << bFStrings[60]
            << endl;
            getBattle()->getOpponent()->setVictory();
            setIntendedMove(RUN);
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
        
        cout << bFStrings[61] << ":" << endl;
        
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
                oss << ": " << bFStrings[62];
            
            if (pokemon != NULL)
                cout << i+1 << ": " << pokemon->getName() << oss.str() << endl;
        }
        
        if (optional)
            cout << ++i << ": (" << bFStrings[22] << ")" << endl;
        
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
            
            cout << bFStrings[63] << " " << getPokemon(choice-1)->getName()
            << "?" << endl << "1: " << bFStrings[64] << endl << "2: "
            << bFStrings[23] << endl << "3: " << bFStrings[24] << endl
            << "4: (" << bFStrings[22] << ")" << endl;
            
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
                        << bFStrings[65] << endl;
                        rerunn = true;
                    }
                    else if (getCurrent() == choice-1)
                    {
                        cout << getPokemon(choice-1)->getName() << " "
                        << bFStrings[66] << endl;
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
    setIntendedMove(SWITCH);
    
    return true;
}

bool Player::chooseFight()
{
    Pokemon* pokemon = getPokemon();
    
    int playerChoice, j;
    bool canMega, willMegaEvolve = false;
    
    do
    {
        cout << bFStrings[67] << ":" << endl;
        
        for (j = 0; j < MAXMOVES; j++)
        {
            cout << j+1 << ": ";
            
            cout << getPokemonMove(j)->getName() << endl;
        }
        
        canMega = pokemon->canMegaEvolve();
        
        if (canMega)
        {
            cout << ++j << ": " << bFStrings[68];
            
            if (willMegaEvolve)
                cout << " (" << bFStrings[69] << ")";
            
            cout << endl;
        }
        
        cout << ++j << ": (" << bFStrings[70] << ")" << endl;
        cout << ++j << ": (" << bFStrings[22] << ")" << endl;
        
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
                setIntendedMove(FIGHT, playerChoice-1);
            else
                setIntendedMove(MEGA, playerChoice-1);
            break;
    }
    
    return true;
}
