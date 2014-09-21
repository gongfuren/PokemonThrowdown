//
//  abilitydata.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 9/11/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__abilitydata__
#define __PokemonThrowdown__abilitydata__

#include "Ability.h"
#include <iostream>
#include "movedata.h"
#include "constants.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "Battle.h"
#include "Field.h"
#include "Reactor.h"

// Vastly unfinished

#define aclass(ability, rules) \
class ability : public Ability \
{ \
public: \
rules \
ability(Pokemon* pokemon) : Ability(P ## ability, pokemon) {}; \
};

aclass(
       Levitate,
       int onTargeted(int moveID, double& mult)
       {
           if (movelib[moveID].type == GroundType)
           {
               flash();
               mult = 0.0;
               return 1;
           }
           else
               return 0;
       };
       )
aclass(
       Intimidate,
       int onSendOut()
       {
           flash();
           for (int i = 0; i < 2; i++)
           {
               Pokemon* target = getPokemon()->getTrainer()->getBattle()->getParticipants(i)->getPokemon();
               if (target != getPokemon())
                   target->decreaseStat(AttStat, false);
           }
           return 1;
       };
       )
aclass(
       Drizzle,
       int onSendOut()
       {
           if (getPokemon()->getTrainer()->getBattle()->getWeather() != Rain)
           {
               flash();
               getPokemon()->getTrainer()->getBattle()->getField()->initializeWeather(Rain);
               return 1;
           }
           else
               return 0;
       };
       )
aclass(
       Drought,
       int onSendOut()
       {
           if (getPokemon()->getTrainer()->getBattle()->getWeather() != Sunny)
           {
               flash();
               getPokemon()->getTrainer()->getBattle()->getField()->initializeWeather(Sunny);
               return 1;
           }
           else
               return 0;
       };
       )
aclass(
       SandStream,
       int onSendOut()
       {
           if (getPokemon()->getTrainer()->getBattle()->getWeather() != Sandstorm)
           {
               flash();
               getPokemon()->getTrainer()->getBattle()->getField()->initializeWeather(Sandstorm);
               return 1;
           }
           else
               return 0;
       };
       )
aclass(
       SnowWarning,
       int onSendOut()
       {
           if (getPokemon()->getTrainer()->getBattle()->getWeather() != Hail)
           {
               flash();
               getPokemon()->getTrainer()->getBattle()->getField()->initializeWeather(Hail);
               return 1;
           }
           else
               return 0;
       };
       )
aclass(
       Pressure,
       int onSendOut()
       {
           flash();
           std::cout << getPokemon()->getName() << " is exerting its " << abilityStrings[getPokemon()->getAbility()->getID()] << "!" << std::endl;
           return 1;
       };
       int onIncreasePPUsage()
       {
           return 1;
       };
       )
aclass(
       MoldBreaker,
       int onSendOut()
       {
           flash();
           std::cout << getPokemon()->getName() << " breaks the mold!" << std::endl;
           return 1;
       };
       )
aclass(
       SwiftSwim,
       int onModifySpe(double& spe)
       {
           if (getPokemon()->getTrainer()->getBattle()->getField()->getWeather() == Rain)
           {
               spe = 2.0;
               return 1;
           }
           else
               return 0;
       };
       )
aclass(
       ClearBody,
       int onTryLowerStat(bool& isLowered, int whichStat)
       {
           flash();
           std::cout << getPokemon()->getName() << "'s " << statFullStrings[whichStat] << " was not lowered!" << std::endl;
           isLowered = false;
           return 1;
       };
       )
aclass(
       Defiant,
       int onLowerStat()
       {
           flash();
           getPokemon()->increaseStat(AttStat, 2);
           return 1;
       };
       )
aclass(
       HugePower,
       int onAttackMultiplier(double& att)
       {
           att = 2.0;
           return 1;
       };
       )
aclass(
       PurePower,
       int onAttackMultiplier(double& att)
       {
           att = 2.0;
           return 1;
       };
       )
aclass(
       StanceChange,
       int onExecuteMove(Move* whichMove)
       {
           if (getPokemon()->getForm() == 0 && whichMove->getMoveType() != Status)
           {
               flash();
               getPokemon()->formChange(1);
               std::cout << "Changed to Blade Forme!" << std::endl;
               return 1;
           }
           else if (whichMove->getID() == 588)
           {
               flash();
               getPokemon()->formChange(0);
               std::cout << "Changed to Shield Forme!" << std::endl;
               return 1;
           }
           else
               return 0;
       };
       )
aclass(
       SkillLink,
       int onMaxMultiHit()
       {
           return 1;
       };
       )
aclass(
       Technician,
       int onDamageMultiplier(double& damage, Move* whichMove)
       {
           if (damage <= 60)
               damage *= 1.5;
           return 1;
       };
       )
aclass(
       SereneGrace,
       int onAddedEffectChance(int& chance)
       {
           chance *= 2;
           return 1;
       };
       )
aclass(
       DeathlyTouch,
       int onSendOut()
       {
           flash();
           std::cout << getPokemon()->getName() << " has " << abilityStrings[getID()] << "!" << std::endl;
           return 1;
       };
       int onMadeContact(Pokemon* target)
       {
           flash();
           std::cout << target->getName() << " lost all of its HP!" << std::endl;
           target->decreaseHP(target->getStatsStatus(HPStat));
           return 1;
       };
       int onContacted(Pokemon* attacker)
       {
           flash();
           std::cout << attacker->getName() << " lost all of its HP!" << std::endl;
           attacker->decreaseHP(attacker->getStatsStatus(HPStat));
           return 1;
       };
       )

#undef aclass

#endif /* defined(__PokemonThrowdown__abilitydata__) */
