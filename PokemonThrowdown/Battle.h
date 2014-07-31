//
//  Battle.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Battle__
#define __PokemonThrowdown__Battle__

#include "constants.h"
#include "pokedata.h"
#include "Field.h"
#include <string>
using namespace std;

class Trainer;
class Pokemon;
class Move;

struct trainerdata;
struct movedata;

class Battle
// Orchestrates Pokemon battle based on rules of game
// Hosts Field and Trainers which host Side, Slot, Pokemon, Move, Item, etc.
// Displays relevant information regarding battle
{
public:
    Battle();
    ~Battle();
    
    // Start the Battle
    void start();
    
    // Display state of battle participants (i.e. Level, Name, Status, HP)
    void displayState(bool showTurnCount) const;
    
    // Display in-battle summary
    void dispPokeSummary(int slotNumber) const;
    
    // Display summary of specified Pokemon species
    void dispPokeSummary(const pokedata pokemon) const;
    
    // Display in-battle (i.e. with current PP) moves
    void dispPokeMoves(int pokemon) const;
    void dispPokeMoves() const;
    
    // Display currently-set moves for Pokemon of specified species
    void dispPokeMoves(const pokedata pokemon) const;
    
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
    int getPreMoveIDs(int trainer, int pokemon, int moveslot) const;
    int* getPreMoveIDs() const;
    int getNumPlayers() const;
    
    // Mutator functions
    bool setPlayer(Trainer* player);
    bool setOpponent(Trainer* opponent);
    bool setParticipants(Trainer* participant);
    bool setWeather(Weather weather);
    bool setField(Field* field);
    
private:
    // Tick the clock for each turn
    void clockTick();
    
    // Allow user to customize own Trainer and opponent Trainer
    bool chooseTrainer();
    bool customTrainer(trainerdata* t);
    int searchByName(bool p = true) const;
    int browse(bool p = true) const;
    int randomChoice(bool p = true) const;
    void dispMoveInfo(const movedata* m) const;
    bool chosePokemon(int p, bool* r, bool m = true, bool i = true) const;
    
    // Main Battle cycle, calls the respective phases
    void cycle();
    
    // Battle greeting
    void greet() const;
    
    // Have participants choose their lead Pokemon
    void chooseLead();
    
    // Five Battle phases:
    
    // Send out or replace Pokemon
    void summonsPhase();
    // Players choose their actions
    void actionPhase();
    // Right before the fun part (i.e. Pokemon switches)
    void preBattlePhase();
    // The fun part
    void battlePhase();
    // The not-so-fun part
    void postBattlePhase();
    
    // Field events (the only important one so far is starting weather)
    void fieldEvent();
    
    // Display turn count (starts at 1)
    void turnCount() const;
    
    // Tell participants to choose actions
    void actionSelect();
    
    // (Currently messy) functions for judging when a Battle is over
    bool checkWin() const;
    bool battleIsOver() const;
    
    // Sorting priorities
    void sortSpeeds(Trainer* trainers[], int number);
    int speedCompare(const Pokemon* pokemonA, const Pokemon* pokemonB) const;
    void swap(Trainer** trainerA, Trainer** trainerB);
    
    // Data members
    Field* m_field;
    Trainer* m_player;
    Trainer* m_player2;
    Trainer* m_opponent;
    Trainer* m_opponent2;
    Trainer* m_actor;
    Trainer* m_participants[NUMPLAYERS];
    int m_turns;
    int m_numPlayers;
    int m_preMoveIDs[2][MAXPOKEMON][MAXMOVES];
};

#endif /* defined(__PokemonThrowdown__Battle__) */
