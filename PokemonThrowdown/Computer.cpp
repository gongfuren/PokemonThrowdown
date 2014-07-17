//
//  Computer.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/15/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Computer.h"
#include "Pokemon.h"

Computer::Computer(trainerdata h, Battle* battle)
: Trainer(h, battle)
{
    m_difficulty = randInt(0, 2);
}

Computer::~Computer()
{
    
}

void Computer::actionSelect()
{
    actionSelect(m_difficulty);
}

void Computer::actionSelect(int level)
{
    Pokemon* pokemon = getPokemon();
    int attack;
    
    // Level 0: select move at random, Mega Evolve if possible
    if (level == 0 /* temp --> */ || level == 1 || level == 2)
    {
        attack = randInt(0, 3);
        
        if (pokemon->canMegaEvolve())
            setIntendedMove(MegaDecision, attack);
        else
            setIntendedMove(FightDecision, attack);
    }
    else
    {
        return;
    }
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
    int pokemonLeft = 0;
    
    for (int i = 0; i < MAXPOKEMON; i++)
    {
        if (getPokemon(i) != NULL && !getPokemon(i)->isFainted())
        {
            pokemonLeft++;
        }
    }
    
    int choice = randInt(0, pokemonLeft-1);
    
    for (int i = 0; i < MAXPOKEMON; i++)
    {
        if (getPokemon(i) != NULL && !getPokemon(i)->isFainted())
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
