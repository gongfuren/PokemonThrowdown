//
//  Item.h
//  pokemongame
//
//  Created by Ian Cordero on 6/8/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Item__
#define __PokemonThrowdown__Item__

#include <string>

class Pokemon;

class Item
// Represents an Item and its current state (i.e. used, active)
{
public:
    Item(int ID, Pokemon* pokemon);
    ~Item();
    
    int getID() const;
    int getAge() const;
    std::string getName() const;
    Pokemon* getPokemon() const;
    
    bool restrictsChoice() const;
    
    bool endOfTurn();
    void incrementAge();
    void resetAge();
    void applyConsumption();
    void applyEffect();
    
private:
    int m_ID;
    std::string name;
    int m_age;
    
    Pokemon* m_pokemon;
};

#endif /* defined(__PokemonThrowdown__Item__) */
