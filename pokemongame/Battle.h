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

class Battle
// Orchestrates Pokemon battle based on rules of game
// Hosts Field and Trainers which host Side, Slot, Pokemon, Move, Item, etc.
{
public:
    Battle();
    ~Battle();
    
    // Start the Battle
    void start();
    
    // Other Battle functions
    void displayState(bool showTurnCount) const;
    void printMoveInfo() const;
    void applyStatus(Trainer* trainerA, Trainer* trainerB,
                     int whichMove);
    void applyAttack(Trainer* trainerA, Trainer* trainerB,
                     int whichMove) const;
    void applyEffect(Trainer* trainerA, Trainer* trainerB,
                     int whichMove) const;
    void applySideEffects(Trainer* trainer, int whichMove);
    void printPokeInfo(int slotNumber) const;
    void printPokeMoves(int pokemon) const;
    string statusText(Pokemon* pokemon, bool showStats) const;
    void summonEffects();
    void statusEffect(Trainer* trainer) const;
    void checkDead() const;
    
    void customInit();
    void customInit(Trainer* trainer);
    
    // Accessor functions
    Trainer* getPlayer() const;
    Trainer* getOpponent() const;
    Trainer* getParticipants(int i) const;
    Weather getWeather() const;
    Field* getField() const;
    
private:
    void clockTick();
    void cycle();
    void greet() const;
    void chooseLead();
    void summonsPhase();
    void actionPhase();
    void preBattlePhase();
    void battlePhase();
    void postBattlePhase();
    void fieldEvent();
    void turnCount() const;
    void actionSelect();
    bool checkWin() const;
    bool battleIsOver() const;
    void end() const;
    
    void pokeSummary(const PokeData pokemon) const;
    void pokeMoveInfo(const PokeData pokemon) const;
    
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
