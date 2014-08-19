//
//  Item.h
//  pokemongame
//
//  Created by Ian Cordero on 6/8/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Item__
#define __PokemonThrowdown__Item__

#include <iostream>
#include <string>
using namespace std;

class Pokemon;

class Item
// Represents an Item and its current state (i.e. used, active)
{
public:
    Item(int ID, Pokemon* pokemon);
    ~Item();
    
    int getID() const;
    int getAge() const;
    string getName() const;
    Pokemon* getPokemon() const;
    
    bool restrictsChoice() const;
    
    void incrementAge();
    void resetAge();
    void applyConsumption();
    void applyEffect();
    
private:
    int m_ID;
    string name;
    int m_age;
    
    Pokemon* m_pokemon;
};

#endif /* defined(__PokemonThrowdown__Item__) */
