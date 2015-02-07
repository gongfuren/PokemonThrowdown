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
    enum Effectiveness
    {
        EF0 = 0, EF5 = 50, EF1 = 100, EF2 = 200
    };
    
    enum ID
    {
        Normal = 0, Grass, Fire, Water, Electric, Flying, Ground, Rock, Ice, Bug, Poison, Fighting, Psychic, Ghost, Dark, Steel, Dragon, Fairy, Light, Neutral
    };

    Type();
    
    Type(ID iD);
    
    double getMultiplier(const Type* attackingType) const;
    
    ID getID() const;
    
    static const int MaxNumTypes = 20;
    
private:
    static constexpr Effectiveness Effectivenesses[MaxNumTypes][MaxNumTypes] = {
        // Attacking Type
        //NRM GRS FIR  WTR  ELE  FLY  GND  RCK  ICE  BUG  PSN  FGT  PSY  GHO  DRK  STL  DRG  FRY  LGT  NTL
        {EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF2, EF1, EF0, EF1, EF1, EF1, EF1, EF1, EF1}, // NRM Defending Type
        {EF1, EF5, EF2, EF5, EF5, EF2, EF5, EF1, EF2, EF2, EF2, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1}, // GRS
        {EF1, EF5, EF5, EF2, EF1, EF1, EF2, EF2, EF5, EF5, EF1, EF1, EF1, EF1, EF1, EF5, EF1, EF5, EF1, EF1}, // FIR
        {EF1, EF2, EF5, EF5, EF2, EF1, EF1, EF1, EF5, EF1, EF1, EF1, EF1, EF1, EF1, EF5, EF1, EF1, EF1, EF1}, // WTR
        {EF1, EF1, EF1, EF1, EF5, EF5, EF2, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF5, EF1, EF1, EF1, EF1}, // ELE
        
        {EF1, EF5, EF1, EF1, EF2, EF1, EF0, EF2, EF2, EF5, EF1, EF5, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1}, // FLY
        {EF1, EF2, EF1, EF2, EF0, EF1, EF1, EF5, EF2, EF5, EF5, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1}, // GND
        {EF5, EF2, EF5, EF2, EF1, EF5, EF2, EF1, EF1, EF1, EF1, EF2, EF1, EF1, EF1, EF2, EF1, EF1, EF1, EF1}, // RCK
        {EF1, EF1, EF2, EF1, EF1, EF1, EF1, EF2, EF5, EF1, EF1, EF2, EF1, EF1, EF1, EF2, EF1, EF1, EF1, EF1}, // ICE
        {EF1, EF1, EF2, EF1, EF1, EF2, EF5, EF2, EF1, EF1, EF1, EF5, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1}, // BUG
        
        {EF1, EF5, EF1, EF1, EF1, EF1, EF2, EF1, EF1, EF5, EF5, EF5, EF2, EF1, EF1, EF1, EF1, EF5, EF1, EF1}, // PSN
        {EF1, EF1, EF1, EF1, EF1, EF2, EF1, EF5, EF1, EF5, EF1, EF1, EF2, EF1, EF5, EF1, EF1, EF2, EF5, EF1}, // FGT
        {EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF2, EF1, EF5, EF5, EF2, EF2, EF1, EF1, EF1, EF1, EF1}, // PSY
        {EF0, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF5, EF5, EF0, EF1, EF2, EF2, EF1, EF1, EF1, EF2, EF1}, // GHO
        {EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF2, EF1, EF2, EF0, EF5, EF5, EF1, EF1, EF2, EF2, EF1}, // DRK
        
        {EF5, EF5, EF2, EF1, EF1, EF5, EF2, EF5, EF5, EF5, EF0, EF2, EF5, EF1, EF1, EF5, EF5, EF5, EF1, EF1}, // STL
        {EF1, EF5, EF5, EF5, EF5, EF1, EF1, EF1, EF2, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF2, EF2, EF1, EF1}, // DRG
        {EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF5, EF2, EF5, EF1, EF1, EF5, EF2, EF0, EF1, EF1, EF1}, // FRY
        {EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF5, EF2, EF1, EF1, EF1, EF5, EF1}, // LGT
        {EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1, EF1} // NTL
    };
    
    ID iD;
};

#endif /* defined(__PokemonThrowdown__Type__) */
