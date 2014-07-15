//
//  Trainer.cpp
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Trainer.h"
#include "trainerdata.h"
#include "Battle.h"
#include "strings.h"

#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

Trainer::Trainer(trainerdata h, Battle* battle)
: m_battle(battle)
{
    m_current = -1;
    m_name = h.name;
    m_title = h.title;
    m_male = h.male;
    m_victory = false;
    m_reward = 0;
    m_intendedMove = NoDecision;
    m_usedMega = false;
    m_reward = h.reward;
    
    for (int i = 0; i < 6; i++)
    {
        pokedata protomon = pokelib[h.pokemonIDs[i]];
        m_pokemon[i] = new Pokemon(protomon, this);
    }
}

Trainer::~Trainer()
{
    for (int i = 0; i < MAXPOKEMON; i++)
        delete m_pokemon[i];
}

int Trainer::getIntendedMove() const
{
    return m_intendedMove;
}

bool Trainer::setIntendedMove(BattleDecision move, int attack)
{
    if (move == FightDecision || move == MegaDecision)
        getPokemon()->setIntendedMove(attack);
    
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

string Trainer::getTitleName() const
{
    string h = getTitle();
    h += " ";
    h += getName();
    return h;
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
    cout << m_title << " " << m_name << " " << "sent out" << " "
    << m_pokemon[m_current]->getName() << "!" << endl;
    
    for (int i = 0; i < MAXPOKEMONPERPLAYER; i++)
        m_pokemonOut[i] = m_pokemon[m_current];
}

void Trainer::switchPokemon(bool optional)
{
    if (optional)
    {
        cout << getTitleName() << " " << "withdrew" << " "
        << getPokemon()->getName() << "!" << endl;
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
    
    int pokeHP = pokemon->getStats(HPStat);
    int pokeTotalHP = pokemon->getBStats(HPStat);
    
    string pokeHPBar = statFullStrings[HPStat];
    pokeHPBar += ":[";
    
    int bar = static_cast<double>(static_cast<double>(pokeHP) /
                                  static_cast<double>(pokeTotalHP))
                                    * HPBARLENGTH;
    
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
    
    string pokeGen;
    
    switch (pokemon->getGender())
    {
        case Male:
            pokeGen = genderStrings[Male];
            break;
        case Female:
            pokeGen = genderStrings[Female];
            break;
        case NoGender:
            pokeGen = genderStrings[NoGender];
            break;
        case Genderless:
            pokeGen = genderStrings[Genderless];
            break;
    }
    
    string pokeStatus = getBattle()->statusText(pokemon, true);
    
    cout << "Lv" << " " << pokemon->getLevel() << " " << pokeName
    << ' ' << pokeGen << ' ' << pokeStatus << ' ' << generateBalls() << endl
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

void Trainer::checkFaint()
{
    for (int i = 0; i < MAXPOKEMONPERPLAYER; i++)
        m_pokemonOut[i]->checkFaint();
}

bool Trainer::replacePokemon()
{
    return trainerSummon(false);
}

bool Trainer::chooseBag() const
{
    // No bag implementation since focus is on competitive
    // (no using items, among other things) battling
    cout << "You can't do that right now." << endl;
    
    return false;
}