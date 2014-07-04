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
// Displays relevant information regarding battle
{
public:
    Battle();
    ~Battle();
    
    // Allow user to customize own Trainer and opponent Trainer
    // TODO: allow more customization than 4 Trainers with preset Pokemon
    // teams as is implemented at the moment
    void customInit(Trainer* trainer);
    
    // Start the Battle
    void start();
    
    // Display state of battle participants (i.e. Level, Name, Status, HP)
    void displayState(bool showTurnCount) const;
    
    // TODO: move these 4 into Pokemon
    void applyStatus(Trainer* trainerA, Trainer* trainerB,
                     int whichMove);
    void applyAttack(Trainer* trainerA, Trainer* trainerB,
                     int whichMove) const;
    void applyEffect(Trainer* trainerA, Trainer* trainerB,
                     int whichMove) const;
    void applySideEffects(Trainer* trainer, int whichMove);
    
    // Display in-battle summary
    void dispPokeSummary(int slotNumber) const;
    
    // Display summary of specified Pokemon species
    void dispPokeSummary(const PokeData pokemon) const;
    
    // Display in-battle (i.e. with current PP) moves
    void dispPokeMoves(int pokemon) const;
    void dispPokeMoves() const;
    
    // Display currently-set moves for Pokemon of specified species
    void dispPokeMoves(const PokeData pokemon) const;
    
    // TODO: move into Pokemon
    string statusText(Pokemon* pokemon, bool showStats) const;
    
    // Cast effects (i.e. Abilities) when Pokemon is "summoned" (sent out)
    void summonEffects();
    
    // TODO: implement appropriately
    void statusEffect(Trainer* trainer) const;
    
    // Check if any Pokemon have fainted
    void checkFaint() const;
    
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
    
    int m_turns;
    int initStage;
};

#endif /* defined(__pokemongame__Battle__) */
