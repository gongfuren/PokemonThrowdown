//
//  Pokemon.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Pokemon__
#define __pokemongame__Pokemon__

#include "constants.h"
#include "Move.h"
#include "PokeData.h"

#include <string>
#include <list>
#include <stack>
using namespace std;

class Trainer;
class Slot;
class Item;

class Pokemon
{
public:
    Pokemon(int pokemonID, Trainer* trainer);
    Pokemon(PokeData h, Trainer* trainer);
    ~Pokemon();
    void standardInit(int pokemonID);
    void customInit();
    void transformInit(int pokemonID);
    
    string getName() const;
    Type getType1() const;
    Type getType2() const;
    PokeStatus getStatus() const;
    int getStats(int whichStat) const;
    int getBStats(int whichStat) const;
    int getStatsStatus(int whichStat) const;
    Move* getMove(int whichMove) const;
    Gender getGender() const;
    int getOnMyLevel() const;
    Nature getNature() const;
    PokeAbility getAbility() const;
    Item* getItem() const;
    bool hasCompatMega() const;
    string getDescription() const;
    int getForm() const;
    
    Trainer* getTrainer() const;
    Slot* getSlot() const;
    
    int getIntendedMove() const;
    void setIntendedMove(int choice);
    void setStatus(PokeStatus status);
    void addVStatus(VolatileStatus vstatus);
    void removeVStatus(VolatileStatus vstatus);
    bool hasVStatus(VolatileStatus vstatus);
    
    void removeShortStatus();
    
    void flashAbility() const;
    bool passThroughStatus();
    
    void tick();
    int getToxicTurns() const;
    void setToxicTurns(int turns);
    void setSleepTurns(int turns);
    int getSleepTurns() const;
    int getRampageTurns() const;
    void setRampageTurns(int turns);
    
    void checkDead();
    bool isDead() const;
    void setDead();
    void lowerHP(int howMuch);
    bool increaseHP(int howMuch);
    bool hasMaxHP() const;
    bool lowerStat(int whichStat, bool silent);
    bool lowerStat(int whichStat, int levels);
    bool increaseStat(int whichStat, bool silent);
    bool increaseStat(int whichStat, int levels);
    void restoreStat(int whichStat);
    void clearVolatiles();
    double statMultiplier(int statLevel) const;
    
    void castAbility();
    
    void protectDialogue() const;
    void avoidDialogue() const;
    
    void formChange(int form);
    void megaEvolve();
    bool canMegaEvolve() const;
    
    bool executeMove(Pokemon* target);
    void recordMove(bool successful);
    Move* lastTurnsMove() const;
    Move* moveUsedLast(int turnsAgo) const;
    bool usedProtect(int turnsAgo) const;
    
private:
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
    
    int m_statsStatus[NUMALLSTATS];
    int m_intendedMove;
    
    int m_form;
    
    int m_turnsOut;
    int m_sleepTurns;
    int m_toxicTurns;
    int m_rampageTurns;
    
    Move* m_moves[MAXMOVES];
    stack<Move*> m_moveHistory;
    bool m_dead;
    
    Trainer* m_trainer;
    Slot* m_slot;
};

#endif /* defined(__pokemongame__Pokemon__) */
