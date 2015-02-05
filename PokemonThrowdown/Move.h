//
//  Move.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Move__
#define __PokemonThrowdown__Move__

#include <iostream> 
#include <vector> 

#define string std::string
#define vector std::vector

class Pokemon;
class Moves;
class Type;
class Slot;

//
// Move
// Represents a Pokemon move.
//
class Move
{
public:
    enum Category
    {
        Physical, Special, Status
    };
    
    enum Callback
    {
        BasePowerCallback
    };
    
    enum Priority
    {
        QuickClaw = 8,
        Pursuit = 7,
        SwitchOut = 6,
        HelpingHand = 5,
        Protect = 4,
        FakeOut = 3,
        ExtremeSpeed = 2,
        QuickAttack = 1,
        RegularPriority = 0,
        VitalThrow = -1,
        FocusPunch = -3,
        Revenge = -4,
        Counter = -5,
        Whirlwind = -6,
        TrickRoom = -7
    };
    
    Move(Moves* moves);
    
    string getName() const;
    
    int getPower() const;
    
    int getAccuracy() const;
    
    int getPP() const;
    
    Category getCategory() const;
    
    Priority getPriority() const;
    
    const vector<Slot*> getTargets() const;
    
    void setTarget(Slot* target);
    
    void clearTargets();
    
    Type* getType() const;
    
    Pokemon* getPokemon() const;
    
    virtual void execute();
    
private:
    string name;
    int power;
    int accuracy;
    int pP;
    Category category;
    Priority priority;
    vector<Slot*> targets;
    Type* type;
    int hits;
    Moves* moves;
};

#undef string
#undef vector

#endif /* defined(__PokemonThrowdown__Move__) */
