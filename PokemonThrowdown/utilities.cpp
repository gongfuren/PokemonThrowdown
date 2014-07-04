//
//  utils.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/6/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "constants.h"
#include <cstdlib>

// Auxiliary Function Implementations

// TODO: clean up these functions and their usage
void gyroscope(int& gyro, int& scope, int d)
{
    switch (d)
    {
        case UP:
            gyro = 0;
            scope = -1;
            break;
        case RIGHT:
            gyro = 1;
            scope = 0;
            break;
        case DOWN:
            gyro = 0;
            scope = 1;
            break;
        case LEFT:
            gyro = -1;
            scope = 0;
            break;
        default:
            gyro = 0;
            scope = 0;
            break;
    }
}

int weatherNumber(Weather w)
{
    switch (w)
    {
        case Sunny:
            return 1;
        case Rain:
            return 2;
        case Sandstorm:
            return 3;
        case Hail:
            return 4;
        default:
            return 0;
    }
}

Weather numberWeather(int n)
{
    switch (n)
    {
        case 1:
            return Sunny;
        case 2:
            return Rain;
        case 3:
            return Sandstorm;
        case 4:
            return Hail;
        default:
            return NoWeather;
    }
}

int typeNumber(Type t)
{
    switch (t)
    {
        default: return NOTYPE;  // includes NoType
        case NormalType: return NORMALTYPE;
        case GrassType: return GRASSTYPE;
        case FireType: return FIRETYPE;
        case WaterType: return WATERTYPE;
        case ElectricType: return ELECTRICTYPE;
        case IceType: return ICETYPE;
        case BugType: return BUGTYPE;
        case PoisonType: return POISONTYPE;
        case FightingType: return FIGHTINGTYPE;
        case FlyingType: return FLYINGTYPE;
        case GroundType: return GROUNDTYPE;
        case RockType: return ROCKTYPE;
        case GhostType: return GHOSTTYPE;
        case PsychicType: return PSYCHICTYPE;
        case DragonType: return DRAGONTYPE;
        case DarkType: return DARKTYPE;
        case SteelType: return STEELTYPE;
        case FairyType: return FAIRYTYPE;
        case NeutralType: return NEUTRALTYPE;
        case LightType: return LIGHTTYPE;
    }
}

double typeMultiplier(Type type1, Type type2)
{
    return typeArray[typeNumber(type1)][typeNumber(type2)];
}

double typeMultiplier(Type type1, Type type2, Type type3)
{
    if (type3 == NoType)
        return typeMultiplier(type1, type2);
    else
        return (typeMultiplier(type1, type2) * typeMultiplier(type1, type3));
}

int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    return lowest + (rand() % (highest - lowest + 1));
}

double natureMultiplier(Nature nature, int stat)
{
    return natureArray[nature][stat];
}

Nature returnNature(int whichNature)
{
    switch (whichNature)
    {
        default: return NoNature;
        case HARDY: return HardyNature;
        case LONELY: return LonelyNature;
        case BRAVE: return BraveNature;
        case ADAMANT: return AdamantNature;
        case NAUGHTY: return NaughtyNature;
        case BOLD: return BoldNature;
        case DOCILE: return DocileNature;
        case RELAXED: return RelaxedNature;
        case IMPISH: return ImpishNature;
        case LAX: return LaxNature;
        case TIMID: return TimidNature;
        case HASTY: return HastyNature;
        case SERIOUS: return SeriousNature;
        case JOLLY: return JollyNature;
        case NAIVE: return NaiveNature;
        case MODEST: return ModestNature;
        case MILD: return MildNature;
        case QUIET: return QuietNature;
        case BASHFUL: return BashfulNature;
        case RASH: return RashNature;
        case CALM: return CalmNature;
        case GENTLE: return GentleNature;
        case SASSY: return SassyNature;
        case CAREFUL: return CarefulNature;
        case QUICK: return QuickNature;
    }
}