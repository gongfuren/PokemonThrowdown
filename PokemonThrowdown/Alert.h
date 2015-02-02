//
//  Alert.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Alert__
#define __PokemonThrowdown__Alert__

#include <iostream>
#include "Presentable.h"

//
// Alert
// Represents an up front alert where the user must press 'OK' to continue.
//
class Alert : public Presentable
{
public:
    Alert(std::string text);
    
    std::string getText() const;
    
private:
    std::string text;
};

#endif /* defined(__PokemonThrowdown__Alert__) */
