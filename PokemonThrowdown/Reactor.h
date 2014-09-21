//
//  Reactor.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 9/11/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Reactor__
#define __PokemonThrowdown__Reactor__

class Move;
class Pokemon;

// Vastly unfinished

#define empty { return 0; }

class Reactor
{
public:
    virtual int onTargeted(int moveID, double& mult) empty;
    virtual int onSendOut() empty;
    virtual int onModifySpe(double& spe) empty;
    virtual int onMadeContact(Pokemon* target) empty;
    virtual int onContacted(Pokemon* attacker) empty;
    virtual int onTryLowerStat(bool& isLowered, int whichStat) empty;
    virtual int onLowerStat() empty;
    virtual int onAttackMultiplier(double& att) empty;
    virtual int onExecuteMove(Move* whichMove) empty;
    virtual int onIncreasePPUsage() empty;
    virtual int onMaxMultiHit() empty;
    virtual int onDamageMultiplier(double& damage, Move* whichMove) empty;
    virtual int onAddedEffectChance(int& chance) empty;
};

#undef empty


#endif /* defined(__PokemonThrowdown__Reactor__) */
