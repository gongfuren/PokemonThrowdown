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
class Team;
class Trainer;
class Move;

//
// Pokemon
// Represents a battle Pokemon.
//
class Pokemon
{
public:
    enum Gender
    {
        Male, Female, Genderless
    };
    
    enum Nature
    {
        NoNature
    };
    
    Pokemon(Team* team);
    
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
    
    static string shortDescription(Gender gender);
    
    Trainer* getTrainer() const;
        
    double getCriticalMultiplier() const;
    
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
    Team* team;
};

#undef string

#endif /* defined(__PokemonThrowdown__Pokemon__) */
