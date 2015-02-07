//
//  Computer.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Computer__
#define __PokemonThrowdown__Computer__

#include "Player.h" 

#define override virtual

//
// Computer
// A Player that selects its own actions instead of prompting the user to select
// its actions.
//
class Computer : public Player
{
public:
    Computer(Window* window);
    
    ~Computer();
    
    override void initialSummon();
    
    override void introduceSelf() const;
    
    override void selectAction();
    
    override void selectReplacementPokemon();
};

#undef override

#endif /* defined(__PokemonThrowdown__Computer__) */
