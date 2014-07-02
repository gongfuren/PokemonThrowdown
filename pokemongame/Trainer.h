//
//  Trainer.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Trainer__
#define __pokemongame__Trainer__

#include "Pokemon.h"
#include "TrainerData.h"

#include <string>
using namespace std;

class Battle;
class Move;

class Trainer
{
public:
    Trainer(int trainerAID, Battle* battle);
    Trainer(TrainerData h, Battle* battle);
    virtual ~Trainer();
    void standardInit(int trainerID);
    
    void setCurrent(int current);
    void summonPokemon();
    void switchPokemon(bool optional);
    void summonPokemon(int choice);
    
    void displayState() const;
    
    Battle* getBattle() const;
    string getName() const;
    string getTitle() const;
    bool getMale() const;
    int getReward() const;
    int getCurrent() const;
    Pokemon* getPokemon(int pokemonmon) const;
    Pokemon* getPokemon() const;
    string getPokemonName() const;
    Move* getPokemonMove(int whichMove) const;
    bool getVictory() const;
    void setVictory();
    
    bool canChooseAction() const;
    bool getUsedMega() const;
    void setUsedMega();
    
    virtual void actionSelect() = 0;
    virtual bool isComputer() const = 0;
    
    // Strategy
    int getIntendedMove() const;
    bool setIntendedMove(int move);
    int getIntendedSwitch() const;
    bool setIntendedSwitch(int which);
    
    string generateBalls() const;
    
    void checkDead();
    
private:    
    string m_name;
    string m_title;
    bool m_male;
    int m_reward;
    
    int m_intendedMove;
    int m_intendedSwitch;
    
    bool m_usedMega;
    
    Pokemon* m_pokemonOut[MAXPOKEMONPERPLAYER];
    Pokemon* m_pokemon[MAXPOKEMON];
    Battle* m_battle;
    int m_current;
    bool m_victory;
};

#endif /* defined(__pokemongame__Trainer__) */
