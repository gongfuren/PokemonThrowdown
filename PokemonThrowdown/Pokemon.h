//
//  Pokemon.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Pokemon__
#define __PokemonThrowdown__Pokemon__

#include <iostream>

#define string std::string

class Moves;
class Stats;
class Types;
class Ability;
class Item;
class Status;

//
// Pokemon
// Represents a battle Pokemon.
//
class Pokemon
{
public:
    enum Gender
    {
        Male = 0, Female, Genderless
    };
    
    Pokemon();
    
    ~Pokemon();
    
    string getName() const;
    
    string* getNickname() const;
    
    Moves* getMoves() const;
    
    Stats* getStats() const;
    
    Types* getTypes() const;
    
    Ability* getAbility() const;
    
    Item* getItem() const;
    
    Gender getGender() const;
    
    Status* getStatus() const;
    
    int getLevel() const;
    
    string getFullName() const;
    
    static string description(Gender gender);
    
private:
    string name;
    string* nickname;
    Moves* moves;
    Stats* stats;
    Types* types;
    Ability* ability;
    Item* item;
    Gender gender;
    Status* status;
    int level;
};

#undef string

#endif /* defined(__PokemonThrowdown__Pokemon__) */
