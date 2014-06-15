//
//  Player.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/10/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Player.h"
#include "constants.h"

// Trainer::Trainer(TrainerData h, Battle* battle, bool isComputer)

Player::Player(TrainerData h, Battle* battle)
: Trainer(h, battle, false)
{
    
}

Player::~Player()
{
    
}