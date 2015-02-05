//
//  Slot.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/3/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Slot__
#define __PokemonThrowdown__Slot__

class Pokemon;
class Team;

//
// Slot
// Represents slots on the battlefield owned by a Trainer.
//
class Slot
{
public:
    Slot(Pokemon* pokemon, Team* team);
    
    Pokemon* getPokemon() const;
    
    void setPokemon(Pokemon* pokemon);
    
    void clearPokemon();
    
private:
    Pokemon* pokemon;
    Team* team;
};

#endif /* defined(__PokemonThrowdown__Slot__) */
