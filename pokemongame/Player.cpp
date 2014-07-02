//
//  Player.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/10/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Player.h"
#include "Battle.h"
#include "constants.h"

// Note: Field, Side, Slot, Player, Computer, and Item classes are all "hardly
// implemented", that is, these modules are not being utilized to any
// appreciable extent. TODO: utilize these classes, as well as existing ones
// to improve modularity and organization. Perhaps make new classes as needed.

Player::Player(TrainerData h, Battle* battle)
: Trainer(h, battle)
{
    
}

Player::~Player()
{
    
}

void Player::actionSelect()
{
    if (!canChooseAction())
        return;
    
    Battle* battle = getBattle();
    bool rerun = false;
    
    do
    {
        cout << "What would you like to do?" << endl;
        
        cout << "1: Fight!" << endl
        << "2: Bag" << endl
        << "3: Pokemon" << endl
        << "4: Run" << endl;
        
        int choice;
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                rerun = !battle->chooseFight();
                break;
            case 2:
                rerun = !battle->chooseBag();
                break;
            case 3:
                rerun = !battle->choosePokemon(this);
                break;
            case 4:
                rerun = !battle->chooseRun();
                break;
            default:
                break;
        }
    }
    while (rerun);
    
    battle->summonEffects();
}

bool Player::isComputer() const
{
    return false;
}