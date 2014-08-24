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
#include "utilities.h"

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
    int choice, prog = 0;
    string aref[4];
    bool rerun;
    Battle* battle = getBattle();
    
    if (!canChooseAction())
        return;
    
    do
    {
        rerun = false;
        
        getBattle()->displayState(true);
        
        cout << "What would you like to do?" << endl;
        
        aref[0] = "Fight!";
        aref[1] = "Bag";
        aref[2] = "Pokemon";
        aref[3] = "Run";
        
        choice = selectorGadget(aref, 4, prog, 4, false);
        
        switch (choice)
        {
            case 0:
                rerun = !chooseFight();
                break;
            case 1:
                rerun = !chooseBag();
                break;
            case 2:
                rerun = !choosePokemon();
                break;
            case 3:
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
    int choice, prog = 0;
    string bref[2];
    
    cout << "Are you sure you'd like to run and forfeit the match?" << endl;
    
    bref[0] = "Yes";
    bref[1] = "No";
    
    choice = selectorGadget(bref, 2, prog, 2, false);
    
    switch (choice)
    {
        case 0:
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
    int choice, i, prog = 0;
    bool rerun = false;
    string pref[6], wref[3];
    Pokemon* pokemon;
    
    do
    {
        rerun = false;
        
        cout << "Choose a Pokemon" << ":" << endl;
        
        cout << generateBalls() << endl;
        
        // Summon prompt
        for (i = 0; i < getNumPokemon(); i++)
        {
            ostringstream oss;

            pokemon = getPokemon(i);
            
            if (pokemon == NULL)
                continue;
            
            oss << pokemon->getName();
            
            if (pokemon->getStatus() != HealthyStatus)
                oss << ": " << pokemon->statusText(false);
            
            if (getCurrent() == i && !pokemon->isFainted())
                oss << ": " << "In Battle";
            
            pref[i] = oss.str();
        }
        
        choice = selectorGadget(pref, getNumPokemon(), prog, 6, optional);
        
        if (choice == BACK)
            return false;

        if (choice >= 0 && choice < i)
        {
            if (optional && choice == i)
                return false;
        }
        else
        {
            rerun = true;
            continue;
        }
        
        if (getPokemon(choice) == NULL)
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
            
            cout << "You chose " << getPokemon(choice)->getName() << "." << endl;
            
            wref[0] = "Switch";
            wref[1] = "Summary";
            wref[2] = "Check Moves";
            
            choicee = selectorGadget(wref, 3, prog);
            
            switch (choicee)
            {
                default:
                    rerunn = true;
                    continue;
                case 0:
                    if (getPokemon(choice)->isFainted())
                    {
                        cout << getPokemon(choice)->getName() << " "
                        << "is fainted and cannot battle." << endl;
                        rerunn = true;
                    }
                    else if (getCurrent() == choice)
                    {
                        cout << getPokemon(choice-1)->getName() << " "
                        << "is already out!" << endl;
                        rerunn = true;
                    }
                    break;
                case 1:
                    getBattle()->dispPokeSummary(choice);
                    rerunn = true;
                    break;
                case 2:
                    getBattle()->dispPokeMoves(choice);
                    rerunn = true;
                    break;
                case BACK:
                    rerun = true;
                    rerunn = false;
                    break;
            }
            
        } while (rerunn);
        
    }
    while (rerun);
    
    // Set intended switch
    setIntendedSwitch(choice);
    setIntendedMove(SwitchDecision);
    
    return true;
}

bool Player::chooseFight()
{
    Pokemon* pokemon = getPokemon();
    Move* move;
    int playerChoice, i, j, prog;
    bool canMega, willMegaEvolve = false, hasMovesLeft = false;
    
    string mvref[4], meref[2];
    int mvsize, mesize;
    
    for (i = 0; i < MAXMOVES; i++)
    {
        move = getPokemonMove(i);
        if (move == NULL)
            continue;
        if (move->getCurrentPP() > 0)
            hasMovesLeft = true;
    }
    if (!hasMovesLeft)
    {
        playerChoice = MAXMOVES;
        goto set_move___;
    }
    
choose_move___:
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
            ostringstream tmp;
            tmp << move->getName() << " (" << move->getCurrentPP() << "/"
            << move->getPP() << ")";
            mvref[j++] = tmp.str();
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
    
    if (getPokemonMove(playerChoice)->getCurrentPP() == 0)
    {
        cout << "No PP remaining for selected move!" << endl;
        goto choose_move___;
    }
    
set_move___:
    if (!willMegaEvolve)
        setIntendedMove(FightDecision, playerChoice);
    else
        setIntendedMove(MegaDecision, playerChoice);
    
    return true;
}
