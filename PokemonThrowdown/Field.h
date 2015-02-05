//
//  Field.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 2/2/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Field__
#define __PokemonThrowdown__Field__

#include <vector> 

#define vector std::vector

class Weather;
class Element;
class Window;

//
// Field
// A programmatical representation of the battlefield and its current state.
//
class Field
{
public:
    Field();
    
private:
    Weather* weather;
    vector<Element*> elements;
};

#undef vector

#endif /* defined(__PokemonThrowdown__Field__) */
