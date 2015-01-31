//
//  Type.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Type__
#define __PokemonThrowdown__Type__

//
// Type
// Represents a Pokemon type.
//
class Type
{
public:
    double getMultiplier(const Type& attackingType) const;
    
    enum { Normal = 0, Grass, Fire, Water, Electric, Flying, Ground, Rock, Ice, Bug, Fighting, Psychic, Ghost, Dark, Steel, Fairy, Light, Neutral } typeID;
    static const int MaxNumTypes = 18;
    enum Effectiveness { Non = 0, Not = 50, Reg = 100, Sup = 200 };
    
private:
    static constexpr Effectiveness effectivenesses[MaxNumTypes][MaxNumTypes] = {
        // Defending Type
        //NRM GRS FIR  WTR  ELE  FLY  GND  RCK  ICE  BUG  FGT  PSY  GHO  DRK  STL  FRY  LGT  NTL
        Reg, Reg, Reg, Reg, Reg, Reg, Reg, Not, Reg, Reg, Reg, Reg, Non, Reg, Not, Reg, Reg, Reg, // NRM Attacking Type
        Reg, Not, Not, Sup, Reg, Not, Sup, Sup, Reg, Reg, Reg, Reg, Reg, Reg, Not, Reg, Reg, Reg, // GRS
        Reg, Sup, Not, Not, Reg, Reg, Reg, Not, Sup, Sup, Reg, Reg, Reg, Reg, Sup, Reg, Reg, Reg, // FIR
        Reg, Reg, Sup, Reg, Reg, Reg, Sup, Sup, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // WTR
        Reg, Reg, Reg, Sup, Reg, Sup, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // ELE
        
        Reg, Sup, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Sup, Sup, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // FLY
        Reg, Reg, Sup, Reg, Sup, Reg, Reg, Sup, Reg, Reg, Reg, Reg, Reg, Reg, Sup, Reg, Reg, Reg, // GND
        Reg, Reg, Sup, Reg, Reg, Sup, Reg, Reg, Sup, Sup, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // RCK
        Reg, Sup, Reg, Reg, Reg, Sup, Sup, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // ICE
        Reg, Sup, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Sup, Reg, Sup, Reg, Reg, Reg, Reg, // BUG
        
        Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // FGT
        Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // PSY
        Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // GHO
        Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // DRK
        Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // STL
        
        Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // FRY
        Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // LGT
        Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, Reg, // NTL
    };
};

#endif /* defined(__PokemonThrowdown__Type__) */
