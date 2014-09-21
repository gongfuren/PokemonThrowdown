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
#include <vector>

class Trainer;
class Slot;
class Item;
class Ability;
class Substitute;

class Pokemon
// Represents a Battle-ready Pokemon and its current state
{
public:
    Pokemon(pokedynamicdata h, Trainer* trainer, int wp);
    ~Pokemon();
    
    // Accessor functions
    std::string getName() const;
    std::string getNickname() const;
    Type getType1() const;
    Type getType2() const;
    PokeStatus getStatus() const;
    double getStats(int whichStat) const;
    int getBaseStats(int whichStat) const;
    int getStatsStatus(int whichStat) const;
    Move* getMove(int whichMove) const;
    Gender getGender() const;
    int getLevel() const;
    Nature getNature() const;
    Ability* getAbility() const;
    Item* getItem() const;
    bool hasCompatMegaStone() const;
    std::string getDescription() const;
    int getForm() const;
    int getID() const;
    Trainer* getTrainer() const;
    Slot* getSlot() const;
    const std::stack<Move*>* getMoveHistory() const;
    int getTurnsOut() const;
    Move* getLockedMove() const;
    int getIntendedMove() const;
    bool isFainted() const;
    
    // Secondary accessor functions
    void pushTarget(Pokemon* target);
    Pokemon* popTarget();
    const std::stack<Pokemon*>* getTargets() const;
    const std::vector<Pokemon*>* getOpponents() const;
    const std::vector<Pokemon*>* getAdjacent() const;
    
    void initializeAbility(int whichAbility);

    // Set functions
    void setIntendedMove(int choice, Pokemon* target = NULL);
    bool setStatus(PokeStatus status, bool rest = false);
    void setFainted();
    
    // Remove functions
    void removeStatus();
    void removeVStatuses();
    void removeVStatus(VolatileStatus vstatus);
    void onShortStatusExpire();
    
    // Add functions
    void addVStatus(VolatileStatus vstatus);
    
    // Has functions
    bool hasVStatus(VolatileStatus vstatus) const;
    
    // Other
    void statusEffect();
    void checkFaint();
    bool hasMaxHP() const;
    void decreaseHP(int howMuch);
    bool increaseHP(int howMuch);
    bool decreaseStat(int whichStat, bool silent = false);
    bool decreaseStat(int whichStat, int levels);
    bool increaseStat(int whichStat, bool silent = false);
    bool increaseStat(int whichStat, int levels);
    void restoreStat(int whichStat);
    void clearVolatiles();
    bool lockMove(Move* m);
    bool unlockMove();
    bool passThroughStatus();
    
    // tick()
    // Do something on each turn tick: i.e. increment turns out
    void tick();
    
    // Battle serving
    std::string statusText(bool showStats) const;
    
    // Status state
    int getToxicTurns() const;
    void setToxicTurns(int turns);
    void setSleepTurns(int turns);
    int getSleepTurns() const;
    int getRampageTurns() const;
    void setRampageTurns(int turns);
    void decTauntTurns();
    
    void onSendOut();
    
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
    void applyAttack(Pokemon* target, Move* move, bool silent = false);
    void applyAttackerEffect(Pokemon* target, Move* move, int damage = 0);
    void applyTargetEffect(Pokemon* target, Move* move, int damage = 0);
    void applySideEffects(Move* move);
    
    void protectDialogue() const;
    void avoidDialogue() const;
    
    // Data members
    std::string m_name;
    std::string m_nickname;
    int m_ID;
    Type m_type1;
    Type m_type2;
    PokeStatus m_status;
    std::list<VolatileStatus> m_vstatuses;
    int m_baseStats[NUMSTATS];
    int m_IVs[NUMSTATS];
    int m_EVs[NUMSTATS];
    Gender m_gender;
    int m_level;
    Nature m_nature;
    Ability* m_ability;
    Item* m_item;
    std::string m_description;
    
    // The state (how many increases/decreases) of each stat
    int m_statsStatus[NUMALLSTATS];
    
    // Intended move slot number
    int m_intendedMove;
    Move* m_locked;
    
    // Opponents
    std::vector<Pokemon*> m_opponents;
    std::vector<Pokemon*> m_adjacent;
    
    // Intended target
    std::stack<Pokemon*> m_targets;
    
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
    Substitute* m_sub;
    
    // Move slots and history
    Move* m_moves[MAXMOVES+1];
    std::stack<Move*> m_moveHistory;
    
    // Keep track of Slot position and owning Trainer
    Trainer* m_trainer;
    Slot* m_slot;
};

class Substitute
{
public:
    Substitute(int HP, Pokemon* pokemon) { s_HP = HP; s_pokemon = pokemon; };
    int getHP() const { return s_HP; };
    bool decreaseHP(int howMuch);
    
private:
    Pokemon* s_pokemon;
    int s_HP;
};

#endif /* defined(__PokemonThrowdown__Pokemon__) */
