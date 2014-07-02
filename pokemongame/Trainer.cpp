//
//  Trainer.cpp
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Trainer.h"
#include "TrainerData.h"
#include "Battle.h"

#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

Trainer::Trainer(int trainerAID, Battle* battle)
: m_battle(battle), m_current(-1), m_name(""), m_title(""), m_male(false), m_victory(false), m_reward(0), m_intendedMove(NODECIS), m_usedMega(false)
{
    for (int i = 0; i < MAXPOKEMON; i++)
        m_pokemon[i] = NULL;
    
    // Standard Initialization:
    
    standardInit(trainerAID);
}

Trainer::Trainer(TrainerData h, Battle* battle)
: m_battle(battle), m_current(-1), m_name(""), m_title(""), m_male(false), m_victory(false), m_reward(0), m_intendedMove(NODECIS), m_usedMega(false)
{
    m_name = h.name;
    m_title = h.title;
    m_male = h.male;
    m_reward = h.reward;
    
    for (int i = 0; i < 6; i++)
    {
        PokeData protomon = pokelib[h.pokemonIDs[i]];
        m_pokemon[i] = new Pokemon(protomon, this);
    }
}

Trainer::~Trainer()
{
    for (int i = 0; i < MAXPOKEMON; i++)
        delete m_pokemon[i];
}

void Trainer::standardInit(int trainerID)
{
    m_name = trainerlib[trainerID].name;
    m_title = trainerlib[trainerID].title;
    m_male = trainerlib[trainerID].male;
    m_reward = trainerlib[trainerID].reward;
    
    for (int i = 0; i < MAXPOKEMON; i++)
    {
        if (trainerlib[trainerID].pokemonIDs[i] != -1)
            m_pokemon[i] = new Pokemon(trainerlib[trainerID].pokemonIDs[i], this);
        else
            m_pokemon[i] = new Pokemon(randInt(0, MAXNUMPOKEMON-1), this);
    }
}

int Trainer::getIntendedMove() const
{
    return m_intendedMove;
}

bool Trainer::setIntendedMove(int move)
{
    m_intendedMove = move;
    
    return true;
}

Battle* Trainer::getBattle() const
{
    return m_battle;
}

string Trainer::getName() const
{
    return m_name;
}

string Trainer::getTitle() const
{
    return m_title;
}

bool Trainer::getMale() const
{
    return m_male;
}

int Trainer::getReward() const
{
    return m_reward;
}

int Trainer::getCurrent() const
{
    return m_current;
}

Pokemon* Trainer::getPokemon(int pokemonmon) const
{
    return m_pokemon[pokemonmon];
}

Pokemon* Trainer::getPokemon() const
{
    return m_pokemon[m_current];
}

bool Trainer::getVictory() const
{
    return m_victory;
}

void Trainer::setVictory()
{
    m_victory = true;
}

void Trainer::setCurrent(int current)
{
    m_current = current;
}

void Trainer::summonPokemon()
{
    cout << m_title << " " << m_name << " sent out " << m_pokemon[m_current]->getName() << "!" << endl;
    
    for (int i = 0; i < MAXPOKEMONPERPLAYER; i++)
        m_pokemonOut[i] = m_pokemon[m_current];
}

void Trainer::switchPokemon(bool optional)
{
    if (optional)
    {
        cout << getTitle() << " " << getName() << " withdrew " << getPokemon()->getName() << "!" << endl;
        getPokemon()->clearVolatiles();
    }
    
    cout << generateBalls() << endl;
    
    summonPokemon(m_intendedSwitch);
}

int Trainer::getIntendedSwitch() const
{
    return m_intendedSwitch;
}

bool Trainer::canChooseAction() const
{
    Pokemon* pokemon = getPokemon();
    
    if (pokemon->hasVStatus(RampageVStatus))
        return false;
    else
        return true;
}

bool Trainer::getUsedMega() const
{
    return m_usedMega;
}

void Trainer::setUsedMega()
{
    m_usedMega = true;
}

bool Trainer::setIntendedSwitch(int which)
{
    m_intendedSwitch = which;
    
    return true;
}

void Trainer::summonPokemon(int choice)
{
    if (choice == 0)   // start of battle
    {
        if (m_current != -1)
        {
            Pokemon* swapper = m_pokemon[0];
            m_pokemon[0] = m_pokemon[m_current];
            m_pokemon[m_current] = swapper;
        }
        
        m_current = 0;
        summonPokemon();
        return;
    }
    
    Pokemon* swapper = m_pokemon[choice];
    m_pokemon[choice] = m_pokemon[m_current];
    m_pokemon[m_current] = swapper;

    summonPokemon();
}

string Trainer::generateBalls() const
{
    string pokes = "";
    
    for (int i = 0; i < MAXPOKEMON; i++)
    {
        if (getPokemon(i) == NULL)
            pokes += '.';
        else
        {
            if (getPokemon(i)->getStatus() == HealthyStatus)
                pokes += 'O';
            else if (getPokemon(i)->getStatus() == FaintStatus)
                pokes += '*';
            else
                pokes += '0';
        }
    }
    
    return pokes;
}

void Trainer::displayState() const
{
    Pokemon* pokemon = getPokemon();
    
    int pokeHP = pokemon->getStats(HPSTAT);
    int pokeTotalHP = pokemon->getBStats(HPSTAT);
    
    string pokeHPBar = "HP:[";
    
    int bar = static_cast<double>(static_cast<double>(pokeHP) /
                                  static_cast<double>(pokeTotalHP)) * HPBARLENGTH;
    
    for (int i = 0; i < HPBARLENGTH; i++)
    {
        if (i < bar)
            pokeHPBar += '%';
        else
            pokeHPBar += ' ';
    }
    
    pokeHPBar += "] ";
    
    if (!isComputer())
    {
        ostringstream o;
        o << pokeHP << '/' << pokeTotalHP;
        pokeHPBar += o.str();
    }
    
    string pokeName = pokemon->getName();
    
    char pokeGen;
    
    switch (pokemon->getGender())
    {
        case Male:
            pokeGen = 'M';
            break;
        case Female:
            pokeGen = 'F';
            break;
        case NoGender:
        case Ungendered:
            pokeGen = ' ';
            break;
    }
    
    string pokeStatus = getBattle()->statusText(pokemon, true);
    
    cout << "Lv " << pokemon->getOnMyLevel() << " " << pokeName << ' '
    << pokeGen << ' ' << pokeStatus << ' ' << generateBalls() << endl
    << pokeHPBar << endl;

}

string Trainer::getPokemonName() const
{
    return getPokemon()->getName();
}

Move* Trainer::getPokemonMove(int whichMove) const
{
    return getPokemon()->getMove(whichMove);
}

void Trainer::checkDead()
{
    for (int i = 0; i < MAXPOKEMONPERPLAYER; i++)
        m_pokemonOut[i]->checkDead();
}