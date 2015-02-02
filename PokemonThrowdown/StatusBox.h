//
//  StatusBox.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/1/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__StatusBox__
#define __PokemonThrowdown__StatusBox__

#include "Presentable.h"
#include <vector> 
#include "Pokemon.h"
#include <iostream>

#define vector std::vector
#define string std::string

struct HPBar;

class StatusBox : public Presentable
{
public:
    enum StatusToken
    {
        Healthy, Poison, Burn, Paralyze, Sleep, Freeze, Faint
    };
    
    enum VolatileToken
    {
        Confuse, Attract, FocusEnergy, Rollout, Protect, FocusPunch, PerishSong
    };
    
    StatusBox(Pokemon* pokemon);
    
    ~StatusBox();
    
    int getHP() const;
    
    int getHPTotal() const;
    
    StatusToken* getStatusToken() const;
    
    vector<VolatileToken> getVolatileTokens() const;
    
    int getLevel() const;
    
    Pokemon::Gender getGender() const;
    
    string getPokemonName() const;
    
private:
    struct { int magnitude; int amplitude; } hPBar;
    StatusToken* statusToken;
    vector<VolatileToken> volatileTokens;
    int level;
    Pokemon::Gender gender;
    string name;
};

#undef vector
#undef string

#endif /* defined(__PokemonThrowdown__StatusBox__) */
