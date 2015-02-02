//
//  Trainer.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include <iostream>
#include "Trainer.h"
#include "Team.h"

using namespace std;

Trainer::Trainer()
{
    title = "PKMN Trainer";
    name = "Red";
    team = new Team();
    gender = Male;
}

Trainer::~Trainer()
{
    delete team;
}

string Trainer::getTitle() const
{
    return title;
}

string Trainer::getName() const
{
    return name;
}

Team* Trainer::getTeam() const
{
    return team;
}

Trainer::Gender Trainer::getGender() const
{
    return gender;
}

string Trainer::getTitleAndName() const
{
    return title + " " + name;
}