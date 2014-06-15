//
//  Battle.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Battle__
#define __pokemongame__Battle__

#include "constants.h"
#include "PokeData.h"
#include "Field.h"
#include <string>
using namespace std;

class Trainer;
class Pokemon;
class Move;

// Battle class
// Orchestrates Pokemon battle based on rules of game
// Controls all subclasses
class Battle
{
public:
    // Construction
    Battle();
    ~Battle();
    
    // Battle flow functions
    void start();
    void clockworkTick();
    void cycle();
    
    void summonsPhase();
    void actionPhase();
    void preBattlePhase();
    void battlePhase();
    void postBattlePhase();
    
    bool battleIsOver() const;
    
    // Other battle functions
    void greet() const;
    void displayState(bool showTurnCount) const;
    void fieldEvent();
    void turnCount() const;
    void actionSelect();
    bool chooseFight();
    void printMoveInfo() const;
    void applyStatus(Trainer* trainerA, Trainer* trainerB,
                     int whichMove);
    void applyAttack(Trainer* trainerA, Trainer* trainerB,
                     int whichMove) const;
    void applyEffect(Trainer* trainerA, Trainer* trainerB,
                     int whichMove) const;
    void applySideEffects(Trainer* trainer, int whichMove);
    bool chooseBag() const;
    bool choosePokemon(Trainer* trainer) const;
    bool replacePokemon(Trainer* trainer) const;
    void printPokeInfo(int slotNumber) const;
    void printPokeMoves(int pokemon) const;
    string statusText(Pokemon* pokemon, bool showStats) const;
    bool playerSummon(bool optional) const;
    void opponentSummon(Trainer* trainer, bool optional) const;
    void summonEffects();
    bool chooseRun() const;
    void statusEffect(Trainer* trainer) const;
    void checkDead() const;
    bool checkWin() const;
    void end() const;
    void pokeSummary(const PokeData pokemon) const;
    void pokeMoveInfo(const PokeData pokemon) const;
    
    // Initialization
    void customInit();
    void customInit(Trainer* trainer);
    void chooseLead();
    
    // Accessor functions
    Trainer* getPlayer() const;
    Trainer* getOpponent() const;
    Trainer* getParticipants(int i) const;
    Weather getWeather() const;
    Field* getField() const;
    
private:
    // Battle helper functions
    void sortSpeeds(Trainer* trainers[], int number);
    int speedCompare(const Pokemon* pokemonA, const Pokemon* pokemonB) const;
    void swap(Trainer** trainerA, Trainer** trainerB);
    
    Field* m_field;
    
    Trainer* m_player;
    Trainer* m_player2;
    Trainer* m_opponent;
    Trainer* m_opponent2;
    
    Trainer* m_actor;
    Trainer* m_participants[NUMPLAYERS];
    
    // Invariant:
    int m_turns;
    int initStage;
};

#endif /* defined(__pokemongame__Battle__) */
