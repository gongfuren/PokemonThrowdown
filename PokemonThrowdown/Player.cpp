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

Player::Player(trainerdata h, Battle* battle)
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
    Move* move;
    int playerChoice, i, j, prog;
    bool canMega, willMegaEvolve = false;
    
    string mvref[4], meref[2];
    int mvsize, mesize;
    
    do
    {
        mvsize = 0;
        mesize = 0;
        prog = 0;
        
        cout << "Choose a move" << ":" << endl;
        
        for (i = 0, j = 0; i < MAXMOVES; i++)
        {
            move = getPokemonMove(i);
            if (move == NULL)
                continue;
            mvref[j++] = move->getName();
        }
        
        mvsize = j;
        
        canMega = pokemon->canMegaEvolve();
        
        if (canMega)
        {
            meref[mesize] = "*Mega Evolution*";
            if (willMegaEvolve)
                meref[mesize] += " (Selected)";
            mesize++;
        }
        
        meref[mesize++] = "(Move Info)";
        
        playerChoice = selectorGadget(mvref, mvsize, prog, 10, true,
                                      meref, mesize);

        if (playerChoice == BACK)
            return false;
        
        if (playerChoice == mvsize+mesize-1)
        {
            getBattle()->dispPokeMoves();
            playerChoice = mvsize+mesize;
            continue;
        }
        
        if (canMega && playerChoice == mvsize+mesize-2)
        {
            if (willMegaEvolve)
            {
                willMegaEvolve = false;
            }
            else
            {
                willMegaEvolve = true;
            }
            
            playerChoice = mvsize+mesize;
        }
        
    }
    while (playerChoice < 0 || playerChoice >= mvsize);
    
    if (!willMegaEvolve)
        setIntendedMove(FightDecision, playerChoice);
    else
        setIntendedMove(MegaDecision, playerChoice);
    
    return true;
}
