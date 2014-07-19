//
//  Move.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Move__
#define __PokemonThrowdown__Move__

#include "constants.h"
#include "movedata.h"

#include <string>
using namespace std;

class Pokemon;

class Move
// Represents a Move and its current state (i.e. PP, charge)
{
public:
    Move(int moveID, Pokemon* pokemon);
    ~Move();
    
    // Accessor Functions
    string getName() const;
    Type getType() const;
    int getDamage() const;
    int getAccuracy() const;
    MoveType getMoveType() const;
    string getDescription() const;
    MoveEffect getEffect() const;
    MoveTarget getTarget() const;
    int getID() const;
    bool getContact() const;
    
    Pokemon* getPokemon() const;
    int getPP() const;
    int getCurrentPP() const;
    int getAge() const;
    
    // Get priority score for Move (for determining attack order)
    int getPriorityScore() const;
    
    // Identify type of Move
    bool isAttack() const;
    bool isThrash() const;
    
    // Increment age of Move
    void incrementAge();
    
    // Reset age of Move
    void resetAge();
    
    // Decrement PP; if 0, return false
    bool decrementCurrentPP();
    
    // Determine if this Move will fail on target
    bool determineFailure(Pokemon* target) const;
    
private:
    int m_ID;
    string m_name;
    Type m_type;
    int m_damage;
    int m_accuracy;
    MoveEffect m_effect;
    int m_PP;
    MoveType m_moveType;
    string m_description;
    MoveTarget m_target;
    bool m_contact;
    
    Pokemon* m_pokemon;
    int m_currentPP;
    int m_age;
    int m_PPUps;
};

#endif /* defined(__PokemonThrowdown__Move__) */
