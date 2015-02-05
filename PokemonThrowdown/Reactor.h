//
//  Reactor.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Reactor__
#define __PokemonThrowdown__Reactor__

#define empty {}

class Pokemon;

//
// Reactor
// An abstract class representing an element that reacts to events during battle.
// Examples are when a Pokemon is sent out (onSendOut) or when a move makes
// contact (onMadeContact)
//
class Reactor
{
public:
    Reactor(Pokemon* pokemon);
    
    Pokemon* getPokemon() const;
    
    virtual void onSendOut() empty;
    
    virtual void onMadeContact() empty;
        
private:
    Pokemon* pokemon;
};

#undef empty

#endif /* defined(__PokemonThrowdown__Reactor__) */
