//
//  Item.h
//  pokemongame
//
//  Created by Ian Cordero on 6/8/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Item__
#define __pokemongame__Item__

#include <iostream>
#include <string>
using namespace std;

class Pokemon;

class Item
{
public:
    Item(int ID);
    ~Item();
    
    int getID() const;
    int getAge() const;
    string getName() const;
    Pokemon* getHolder() const;
    
    bool restrictsChoice() const;
    
    void incAge();
    void resetAge();
    void applyConsumption();
    void applyEffect();
    
private:
    int m_ID;
    int m_age;
    
    Pokemon* m_holder;
};

#endif /* defined(__pokemongame__Item__) */
