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

class Stats;
class Types;
class Ability;
class Item;

//
// Pokemon
// Represents a battle Pokemon.
//
class Pokemon
{
public:
    Pokemon();
    
private:
    std::string name;
    std::string nickname;
    Stats* stats;
    Types* types;
    Ability* ability;
    Item* item;
    enum Gender { Male = 0, Female, Genderless } gender;
};

#endif /* defined(__PokemonThrowdown__Pokemon__) */
