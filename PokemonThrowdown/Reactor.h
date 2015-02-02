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
