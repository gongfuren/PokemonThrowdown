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

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

class Item
// Represents an Item and its current state (i.e. used, active)
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
