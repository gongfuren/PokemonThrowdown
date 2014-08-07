//
//  Computer.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/15/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Computer.h"
#include "Pokemon.h"
#include "Battle.h"
#include "Ability.h"
#include "utilities.h"
#include <stack>
using namespace std;

Computer::Computer(trainerdata h, Battle* battle)
: Trainer(h, battle)
{
    m_difficulty = 1;
}

Computer::~Computer()
{
    
}

void Computer::actionSelect()
{
    Pokemon* pokemon = getPokemon();
    Pokemon* target = getBattle()->getPlayer()->getPokemon();
    
    Move* moves[MAXMOVES];
    int attack, max, bar, numMoves;
    int smartScores[MAXMOVES] = { 0, 0, 0, 0 };
    
    if (!canChooseAction())
        return;
    
    numMoves = 0;
    
    for (int i = 0; i < MAXMOVES; i++)
    {
        moves[i] = getPokemon()->getMove(i);
        if (moves[i] == NULL || moves[i]->getCurrentPP() == 0)
            ;
        else
            numMoves++;
    }
    
    if (numMoves == 0)
    {
        attack = MAXMOVES;
        goto set_move____;
    }
    
    attack = randInt(0, numMoves);
    bar = 0;
    
    // Level 0: select move completely at random
    if (m_difficulty == 0)
        ;
    // Level 1: select most damaging move or status depending on score
    else // (m_difficulty == 1 || m_difficulty == 2)
    {
        for (int i = 0; i < MAXMOVES; i++)
        {
            moves[i] = getPokemon()->getMove(i);
            if (moves[i] == NULL || moves[i]->getCurrentPP() == 0)
            {
                attack = 0;
                break;
            }
            
            if (moves[i]->getMoveType() == Status)
            {
                smartScores[i] = randInt(0, 150);
                
                if (!pokemon->getMoveHistory()->empty())
                {
                    stack<Move*> temp = *pokemon->getMoveHistory();
                    
                    while (!temp.empty() && bar++ < target->getTurnsOut())
                    {
                        Move* mtm = temp.top();
                        temp.pop();
                        
                        if (moves[i] == mtm)
                            smartScores[i] /= 2;
                    }
                }
            }
            else
                smartScores[i] = moves[i]->getDamage();
            
            if (moves[i]->getTarget() == Opponent)
            {
                smartScores[i] *= typeMultiplier(moves[i]->getType(),
                                                 target->getType1(),
                                                 target->getType2());
                
                if (target->getAbility()->getID() == PLevitate
                    && moves[i]->getType() == GroundType)
                    smartScores[i] *= 0;
                
                if (moves[i]->getType() == pokemon->getType1()
                    || moves[i]->getType() == pokemon->getType2())
                    smartScores[i] *= 1.5;
            }
        }
        
        max = 0;
        
        for (int i = 0; i < MAXMOVES; i++)
        {
            if (moves[i] == NULL)
                continue;
            
            if (smartScores[i] > max
                || (smartScores[i] == max && randInt(0, 1) == 1))
            {
                max = smartScores[i];
                attack = i;
            }
        }
    }
    
set_move____:
    if (pokemon->canMegaEvolve())
        setIntendedMove(MegaDecision, attack);
    else
        setIntendedMove(FightDecision, attack);
}

bool Computer::chooseRun()
{
    // Computers should not forfeit
    return false;
}

bool Computer::isComputer() const
{
    return true;
}

bool Computer::choosePokemon()
{
    trainerSummon(true);
    
    return true;
}

bool Computer::trainerSummon(bool optional)
{
    int pokemonLeft = 0, choice;
    
    for (int i = 0; i < getNumPokemon(); i++)
        if (!getPokemon(i)->isFainted())
            pokemonLeft++;
    
    if (pokemonLeft > 1)
        choice = randInt(0, pokemonLeft-2);
    else
        choice = 0;
    
    for (int i = 0; i < getNumPokemon(); i++)
    {
        if (!getPokemon(i)->isFainted())
        {
            if (choice == 0)
            {
                // Set intended switch
                setIntendedSwitch(i);
                setIntendedMove(SwitchDecision);
                
                break;
            }
            else
                choice--;
        }
    }
    
    return true;
}
