//
//  Move.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Move__
#define __pokemongame__Move__

#include "constants.h"
#include "MoveData.h"

#include <string>
using namespace std;

class Pokemon;

class Move
// Represents a Move and its current state (i.e. PP, charge)
{
public:
    Move(int moveID, Pokemon* pokemon);
    Move(MoveData h, Pokemon* pokemon);
    ~Move();
    void standardInit(int moveID);
    
    Pokemon* getPokemon() const;
    string getName() const;
    Type getType() const;
    int getDamage() const;
    int getAccuracy() const;
    int getPP() const;
    MoveType getMoveType() const;
    string getDescription() const;
    MoveEffect getEffect() const;
    MoveTarget getTarget() const;
    int getID() const;
    bool getContact() const;
    int getAge() const;
    
    int getCurrentPP() const;
    void incAge();
    void resetAge();
    void decCurrentPP();
    
    bool determineFailure(Pokemon* target) const;
    bool isAttack() const;
    bool isThrash() const;
    
    int detPriorityScore() const;
    
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

#endif /* defined(__pokemongame__Move__) */
