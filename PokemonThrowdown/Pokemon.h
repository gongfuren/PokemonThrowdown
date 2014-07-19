//
//  Pokemon.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Pokemon__
#define __PokemonThrowdown__Pokemon__

#include "constants.h"
#include "Move.h"
#include "pokedata.h"

#include <string>
#include <list>
#include <stack>
using namespace std;

class Trainer;
class Slot;
class Item;

class Pokemon
// Represents a Battle-ready Pokemon and its current state
{
public:
    Pokemon(pokedata h, Trainer* trainer, int wp);
    ~Pokemon();
    
    // Accessor functions
    string getName() const;
    Type getType1() const;
    Type getType2() const;
    PokeStatus getStatus() const;
    double getStats(int whichStat) const;
    int getBStats(int whichStat) const;
    int getStatsStatus(int whichStat) const;
    Move* getMove(int whichMove) const;
    Gender getGender() const;
    int getLevel() const;
    Nature getNature() const;
    PokeAbility getAbility() const;
    Item* getItem() const;
    bool hasCompatMegaStone() const;
    string getDescription() const;
    int getForm() const;
    int getID() const;
    Trainer* getTrainer() const;
    Slot* getSlot() const;
    const stack<Move*>* getMoveHistory() const;
    int getTurnsOut() const;
    Move* getLockedMove() const;
    
    // Battle state functions
    int getIntendedMove() const;
    void setIntendedMove(int choice);
    bool setStatus(PokeStatus status, bool rest = false);
    void removeStatus();
    void removeVStatuses();
    void addVStatus(VolatileStatus vstatus);
    void removeVStatus(VolatileStatus vstatus);
    bool hasVStatus(VolatileStatus vstatus);
    void removeShortStatus();
    void checkFaint();
    bool isFainted() const;
    void setFainted();
    void lowerHP(int howMuch);
    bool increaseHP(int howMuch);
    bool hasMaxHP() const;
    bool decreaseStat(int whichStat, bool silent);
    bool decreaseStat(int whichStat, int levels);
    bool increaseStat(int whichStat, bool silent);
    bool increaseStat(int whichStat, int levels);
    void restoreStat(int whichStat);
    void clearVolatiles();
    bool lockMove(Move* m);
    bool unlockMove();

    bool passThroughStatus();
    
    // Do something on each turn tick
    void tick();
    
    // Status state
    int getToxicTurns() const;
    void setToxicTurns(int turns);
    void setSleepTurns(int turns);
    int getSleepTurns() const;
    int getRampageTurns() const;
    void setRampageTurns(int turns);
    void decTauntTurns();
    
    void castAbility();
    
    void formChange(int form);
    void megaEvolve();
    bool canMegaEvolve() const;
    
    bool executeMove(Pokemon* target, Move* move = NULL);
    void recordMove(bool successful);
    Move* lastTurnsMove() const;
    Move* moveUsedLast(int turnsAgo) const;
    bool usedProtect(int turnsAgo) const;
    
private:
    // Update state for a transformation
    void transform(int pokemonID);
    
    // Return multiplier for stats
    double statAMultiplier(int statLevel) const;
    double statEMultiplier(int statLevel) const;
    
    void flashAbility() const;
    bool applyStatus(Pokemon* target, Move* move);
    void applyAttack(Pokemon* target, Move* move);
    void applyEffect(Pokemon* target, Move* move, int drain = 0);
    void applySideEffects(Move* move);
    
    void protectDialogue() const;
    void avoidDialogue() const;
    
    // Data members
    string m_name;
    int m_ID;
    Type m_type1;
    Type m_type2;
    PokeStatus m_status;
    list<VolatileStatus> m_vstatuses;
    int m_bStats[NUMSTATS];
    int m_IVs[NUMSTATS];
    int m_EVs[NUMSTATS];
    Gender m_gender;
    int m_level;
    Nature m_nature;
    PokeAbility m_ability;
    Item* m_item;
    string m_description;
    
    // The state (how many increases/decreases) of each stat
    int m_statsStatus[NUMALLSTATS];
    
    // Intended move slot number
    int m_intendedMove;
    Move* m_locked;
    
    // Is this Pokemon fainted?
    bool m_fainted;
    
    // 0 for default
    int m_form;
    
    // Battle state
    int m_turnsOut;
    int m_sleepTurns;
    int m_toxicTurns;
    int m_rampageTurns;
    int m_tauntTurns;
    
    // Move slots and history
    Move* m_moves[MAXMOVES];
    stack<Move*> m_moveHistory;
    
    // Keep track of Slot position and owning Trainer
    Trainer* m_trainer;
    Slot* m_slot;
};

#endif /* defined(__PokemonThrowdown__Pokemon__) */
