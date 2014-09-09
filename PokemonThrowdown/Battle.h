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

class Trainer;
class Pokemon;
class Move;
class Game;

struct trainerdata;
struct movedata;

class Battle
// Orchestrates Pokemon battle based on rules of game
// Hosts Field and Trainers which host Side, Slot, Pokemon, Move, Item, etc.
// Displays relevant information regarding battle
{
public:
    // Construct the Battle
    Battle(Game* game);
    ~Battle();
    
    // Configure the Battle
    bool configure();
    
    // Start the Battle
    void start();
    
    // Accessor functions
    Trainer* getPlayer() const;
    Trainer* getOpponent() const;
    Trainer* getParticipants(int i) const;
    Weather getWeather() const;
    Field* getField() const;
    int getPreMoveIDs(int trainer, int pokemon, int moveslot) const;
    int* getPreMoveIDs() const;
    int getNumPlayers() const;
    Game* getGame();
    
    // Mutator functions
    bool setPlayer(Trainer* player);
    bool setOpponent(Trainer* opponent);
    bool setParticipants(Trainer* participant);
    bool setWeather(Weather weather);
    bool setField(Field* field);
    
    // Display state of battle participants (i.e. Level, Name, Status, HP)
    void displayState(bool showTurnCount) const;
    
    // Display in-battle summary
    void dispPokeSummary(int slotNumber) const;
    
    // Display summary of specified Pokemon species
    void dispPokeSummary(const pokedynamicdata pokemon, bool dynamic = false) const;
    
    // Display in-battle (i.e. with current PP) moves
    void dispPokeMoves(int pokemon) const;
    void dispPokeMoves() const;
    
    // Display currently-set moves for Pokemon of specified species
    void dispPokeMoves(const pokedynamicdata pokemon, bool dynamic = false) const;
    
    // Cast effects (i.e. Abilities) when Pokemon is "summoned" (sent out)
    void summonEffects();
        
    // Check if any Pokemon have fainted
    void checkFaint() const;
    
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
    bool chosePokemon(int p, bool* r, bool m = true, bool i = true, bool dynamic = false, bool custom = false, int ci = -1);
    
    // Main Battle cycle, calls the respective phases
    void cycle();
    
    // Have participants choose their lead Pokemon
    void chooseLead();
    
    // Greeting for battle
    void greet();
    
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
    
    // Functions for judging when a Battle is over
    bool checkWin() const;
    bool battleIsOver() const;
    
    // Sorting priorities
    void sortSpeeds(Trainer* trainers[], int number);
    int speedCompare(const Pokemon* pokemonA, const Pokemon* pokemonB) const;
    void swap(Trainer** trainerA, Trainer** trainerB);
    
    // Data members
    Game* m_game;
    Field* m_field;
    Trainer* m_player;
    Trainer* m_player2;
    Trainer* m_opponent;
    Trainer* m_opponent2;
    Trainer* m_actor;
    Trainer* m_participants[MAXPLAYERS];
    int m_turns;
    int m_numPlayers;
};

#endif /* defined(__PokemonThrowdown__Battle__) */
