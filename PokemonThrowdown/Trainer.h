//
//  Trainer.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Trainer__
#define __PokemonThrowdown__Trainer__

#include "Pokemon.h"
#include "trainerdata.h"

#include <string>

class Battle;
class Move;

class Trainer
// Represents a participant in the Battle, complete with 1-6 of his/her/its
// Pokemon, and his/her/its current state
{
public:
    Trainer(trainerdata h, Battle* battle, int whichTrainer = 0);
    virtual ~Trainer();
    
    void setCurrent(int current);
    void summonPokemon();
    void switchPokemon(bool optional);
    void summonPokemon(int choice);
    
    void displayState() const;
    
    Battle* getBattle() const;
    std::string getName() const;
    std::string getTitle() const;
    std::string getTitleName() const;
    bool getMale() const;
    int getReward() const;
    int getCurrent() const;
    Pokemon* getPokemon(int pokemonmon) const;
    Pokemon* getPokemon() const;
    std::string getPokemonName() const;
    Move* getPokemonMove(int whichMove) const;
    bool getVictory() const;
    void setVictory();
    
    bool canChooseAction() const;
    bool getUsedMega() const;
    void setUsedMega();
    
    virtual void actionSelect() = 0;
    virtual bool isComputer() const = 0;
    virtual bool chooseRun() = 0;
    
    // Strategy
    int getIntendedMove() const;
    bool setIntendedMove(BattleDecision move, int attack = -1);
    int getIntendedSwitch() const;
    bool setIntendedSwitch(int which);
    
    std::string generateBalls() const;
    
    void checkFaint();
    virtual bool choosePokemon() = 0;
    virtual bool trainerSummon(bool optional, bool uTurn = false) = 0;
    bool replacePokemon();
    bool chooseBag() const;
    
    int getNumPokemon() const;
    
private:    
    std::string m_name;
    std::string m_title;
    bool m_male;
    int m_reward;
    
    int m_intendedMove;
    int m_intendedSwitch;
    
    bool m_usedMega;
    
    Pokemon* m_pokemonOut[MAXPOKEMONPERPLAYER];
    Pokemon* m_pokemon[MAXPOKEMON];
    int m_numPokemon;
    Battle* m_battle;
    int m_current;
    bool m_victory;
};

#endif /* defined(__PokemonThrowdown__Trainer__) */
