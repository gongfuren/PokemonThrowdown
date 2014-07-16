//
//  constants.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Constants__
#define __PokemonThrowdown__Constants__

#include <list>
using namespace std;

// Note: This data file does not adhere to an 80 column limit!

template <typename Object>
bool listContains(const list<Object> l, Object o)
{
    typename list<Object>::const_iterator p = find(l.begin(), l.end(), o);
    
    if (p == l.end())
        return false;
    else
        return true;
}

// Global Constants

// TODO: make use of constants a bit more organized
const int NUMDIRS = 4;

enum Direction
{
    Stand, Up, Right, Down, Left
};

enum Stats
{
    HPStat, AttStat, DefStat, SpAStat, SpDStat, SpeStat, AccStat, EvaStat,
    CritStat
};

const int NUMSTATS = 6;

const int NUMALLSTATS = 9;

const double STAT_A[13] = {
    0.25, 0.285, 0.3333, 0.40, 0.50, 0.6666, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0
};

const double STAT_E[13] = {
    0.3333, 0.38, 0.43, 0.5, 0.6, 0.75, 1.00, 1.3333, 1.6666, 2.0, 2.3333,
    2.6666, 3.0
};

const int HPBARLENGTH = 40;

const int MAXMOVES = 4;

enum BattleDecision
{
    NoDecision, FightDecision, BagDecision, SwitchDecision, RunDecision,
    MegaDecision
};

// Change based on battle style
const int NUMSIDES = 2; // Invariant

const int MAXPLAYERSPERSIDE = 1;
const int NUMPLAYERSPERSIDE[NUMSIDES] = { 1, 1 };
const int NUMPLAYERS = 2;
const int MAXPOKEMONPERPLAYER = 1;
const int NUMPOKEMONPERPLAYER[NUMPLAYERS] = { 1, 1 };

const int MAXPOKEMON = 6;
const int MAXPLAYERS = 4;

const int MAXNUMMOVES = 635;
const int MAXNUMPOKEMON = 721;

const int MAXTOTALMOVES = 700;
const int MAXTOTALPOKEMON = 1000;
const int MAXTOTALTRAINERS = 100;
const int MAXTOTALBATTLES = 100;

const int MAXTYPES = 18 + 1 + 2;    // "Actual" types + NoType + Neutral/Light

const double ELE0 = 0.00;
const double ELE5 = 0.50;
const double ELE1 = 1.00;
const double ELE2 = 2.00;

// Attacking Type j, Defending Type i
const double typeArray[MAXTYPES][MAXTYPES] = {
    
 // NO    NRM   GRS   FIR   WTR   ELE   ICE   BUG   PSN   FGT   FLY   GRD   RCK   GHT   PSY   DRG   DRK   STL   FRY   NTL   LIT
    
    ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, // NO
    
    ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE5, ELE0, ELE1, ELE1, ELE1, ELE5, ELE1, ELE1, ELE1, // NRM
    
    ELE1, ELE1, ELE5, ELE5, ELE2, ELE1, ELE1, ELE1, ELE5, ELE1, ELE5, ELE2, ELE2, ELE1, ELE1, ELE5, ELE1, ELE5, ELE1, ELE1, ELE1, // GRS
    
    ELE1, ELE1, ELE2, ELE5, ELE5, ELE1, ELE2, ELE2, ELE1, ELE1, ELE1, ELE1, ELE5, ELE1, ELE1, ELE5, ELE1, ELE2, ELE1, ELE1, ELE5, // FIR
    
    ELE1, ELE1, ELE5, ELE2, ELE5, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE2, ELE2, ELE1, ELE1, ELE5, ELE1, ELE1, ELE1, ELE1, ELE1, // WTR
    
    ELE1, ELE1, ELE5, ELE1, ELE2, ELE5, ELE1, ELE1, ELE1, ELE1, ELE2, ELE0, ELE1, ELE1, ELE1, ELE5, ELE1, ELE1, ELE1, ELE1, ELE5, // ELE
    
    ELE1, ELE1, ELE2, ELE5, ELE5, ELE1, ELE5, ELE1, ELE1, ELE1, ELE2, ELE2, ELE1, ELE1, ELE1, ELE2, ELE1, ELE5, ELE1, ELE1, ELE1, // ICE
    
    ELE1, ELE1, ELE2, ELE5, ELE1, ELE1, ELE1, ELE1, ELE5, ELE5, ELE5, ELE5, ELE1, ELE1, ELE2, ELE1, ELE2, ELE5, ELE5, ELE1, ELE1, // BUG
    
    ELE1, ELE1, ELE2, ELE1, ELE1, ELE1, ELE1, ELE5, ELE5, ELE5, ELE1, ELE5, ELE5, ELE1, ELE1, ELE1, ELE1, ELE0, ELE2, ELE1, ELE1, // PSN
    
    ELE1, ELE2, ELE1, ELE1, ELE1, ELE1, ELE2, ELE5, ELE5, ELE1, ELE5, ELE1, ELE2, ELE0, ELE5, ELE1, ELE2, ELE2, ELE5, ELE1, ELE1, // FGT
    
 // NO    NRM   GRS   FIR   WTR   ELE   ICE   BUG   PSN   FGT   FLY   GRD   RCK   GHT   PSY   DRG   DRK   STL   FRY   NTL   LIT
    
    ELE1, ELE1, ELE2, ELE1, ELE1, ELE5, ELE1, ELE2, ELE1, ELE2, ELE1, ELE1, ELE5, ELE1, ELE1, ELE1, ELE1, ELE5, ELE1, ELE1, ELE1, // FLY
    
    ELE1, ELE1, ELE5, ELE2, ELE1, ELE2, ELE1, ELE5, ELE2, ELE1, ELE0, ELE1, ELE2, ELE1, ELE1, ELE1, ELE1, ELE2, ELE1, ELE1, ELE1, // GRD
    
    ELE1, ELE1, ELE1, ELE2, ELE1, ELE1, ELE2, ELE2, ELE1, ELE5, ELE2, ELE5, ELE1, ELE1, ELE1, ELE1, ELE1, ELE5, ELE1, ELE1, ELE1, // RCK
    
    ELE1, ELE0, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE2, ELE2, ELE1, ELE5, ELE1, ELE1, ELE1, ELE5, // GHT
    
    ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE2, ELE2, ELE1, ELE1, ELE1, ELE1, ELE5, ELE1, ELE0, ELE5, ELE1, ELE1, ELE1, // PSY
    
    ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE2, ELE1, ELE5, ELE0, ELE1, ELE1, // DRG
    
    ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE5, ELE1, ELE1, ELE1, ELE2, ELE2, ELE1, ELE5, ELE1, ELE5, ELE1, ELE2, // DRK
    
    ELE1, ELE1, ELE1, ELE5, ELE5, ELE5, ELE2, ELE1, ELE1, ELE1, ELE1, ELE1, ELE2, ELE1, ELE1, ELE1, ELE1, ELE5, ELE2, ELE1, ELE1, // STL
    
    ELE1, ELE1, ELE1, ELE5, ELE1, ELE1, ELE1, ELE1, ELE5, ELE2, ELE1, ELE1, ELE1, ELE1, ELE1, ELE2, ELE2, ELE5, ELE1, ELE1, ELE1, // FRY
    
    ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, // NTL
    
    ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE1, ELE2, ELE1, ELE1, ELE2, ELE1, ELE1, ELE1, ELE5  // LIT
};

const int NUMNATURES = 26;

const int MEGAFORM = 9;

const double natureArray[NUMNATURES][NUMSTATS-1] = {
    //  ATT  DEF  SPA  SPD  SPE
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.1, 0.9, 1.0, 1.0, 1.0,
    1.1, 1.0, 1.0, 1.0, 0.9,
    1.1, 1.0, 0.9, 1.0, 1.0,
    1.1, 1.0, 1.0, 0.9, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.9, 1.1, 1.0, 1.0, 1.0,
    1.0, 1.1, 1.0, 1.0, 0.9,
    1.0, 1.1, 0.9, 1.0, 1.0,
    1.0, 1.1, 1.0, 0.9, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.9, 1.0, 1.0, 1.0, 1.1,
    1.0, 0.9, 1.0, 1.0, 1.1,
    1.0, 1.0, 0.9, 1.0, 1.1,
    1.0, 1.0, 1.0, 0.9, 1.1,
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.9, 1.0, 1.1, 1.0, 1.0,
    1.1, 0.9, 1.1, 1.0, 1.0,
    1.0, 1.0, 1.1, 1.0, 0.9,
    1.0, 1.0, 1.1, 0.9, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.9, 1.0, 1.0, 1.1, 1.0,
    1.0, 0.9, 1.0, 1.1, 1.0,
    1.0, 1.0, 1.0, 1.1, 0.9,
    1.0, 1.0, 0.9, 1.1, 1.0
};

const int NUMABILITIES = 100;

// Global Enumerators

enum Type {
    NoType, NormalType, GrassType, FireType, WaterType, ElectricType, IceType,
    BugType, PoisonType, FightingType, FlyingType, GroundType, RockType,
    GhostType, PsychicType, DragonType, DarkType, SteelType, FairyType,
    NeutralType, LightType
};

enum Nature
{
    NoNature, HardyNature, LonelyNature, BraveNature, AdamantNature,
    NaughtyNature, BoldNature, DocileNature, RelaxedNature,
    ImpishNature, LaxNature, TimidNature, HastyNature, SeriousNature,
    JollyNature, NaiveNature, ModestNature, MildNature,
    QuietNature, BashfulNature, RashNature, CalmNature, GentleNature,
    SassyNature, CarefulNature, QuickNature
};

// TODO: organize and consolidate move effects
enum MoveEffect
{
    MNoEffect,
    
    MDamage20, MDamage40, MDamageLevel,
    
    MPoison10, MPoison15, MPoison30, MPoison40,
    
    MToxic100,
    
    MBurn10, MBurn15, MBurn30,
    
    MFreeze10, MFreeze50,
    
    MParalyze10, MParalyze15, MParalyze30, MParalyze100,
    
    MConfuse10, MConfuse20, MConfuse100,
    
    MTri20,
    
    MConfuse, MAttract,
    MBurn, MSleep, MParalyze, MToxic, MPoison,
    
    MLowerAtt, MLowerDef, MLowerSpA, MLowerSpD, MLowerSpe,
    MLowerAcc, MLowerEva,
    
    MLowerAcc100,
    
    MLowerAttDef,
    
    MLowerSpD10, MLowerSpD20, MLowerSpD40, MLowerSpA100,
    
    MUpAtt, MUpDef, MUpSpA, MUpSpD, MUpSpe,
    MUpAcc, MUpEva,
    
    MUpDef10, MUpAtt100,
    
    MUpRnd,
    
    MMoveFirst, MMoveFirst2, MSuperpower, MHighCrit,
    MHeal50, MHeal100, MDrain50, MDrain75,
    
    MRecoil25, MRecoil33, MRecoilStrug,
    
    MFlinch10, MFlinch20, MFlinch30, MFlinch100, MCrit100,
    
    MNeverMiss, MOHKO, MMultiHit, MDoubleHit, MRecharge, MOverheat,
    MCloseCombat, MLowerDefSpDSpe,
    
    MUpAtt2, MUpDef2, MUpSpA2, MUpSpD2, MUpSpe2,
    MUpAcc2, MUpEva2,
    
    MUpSpA3, MUpDef3,
    
    MLowerAtt2, MLowerDef2, MLowerSpA2, MLowerSpD2, MLowerSpe2,
    MLowerAcc2, MLowerEva2,
    
    MLowerDefSpDUpAtt2SpA2Spe2,
    
    MUpSpASpD, MUpSpASpDSpe,
    MUpAttSpe, MUpAttDef, MUpAttSpA, MUpDefSpD, MUpAttAcc,
    
    MUpAttSpe2, MUpAll, MUpAll10,
    
    MIgnoreDef100,
    
    MRain, MSun, MHail, MSandstorm, MTrickRoom, MGravity,
    
    MRampage, MProtect, MShield, MFocusPunch,
    MCounter, MRoar, MSuckerPunch,
    
    MPayDay,
    
    MShockDef,
    
    MSelfdestruct,
    
    MSolarbeam, MRazorwind, MSkullbash, MSkyAttack, MSkyDrop,
    MShadowForce, MFly, MDive, MDig, MPhantomForce,
    
    MBind, MWrap, MFireSpin, MWhirlpool, MMagmaStorm, MSandTomb, MStomp, MMinimize, MJumpKick,
    
    MRage, MFuryCut, MTeleport, MDisable, MBatonPass,
    
    MTrap, MPartialTrap,
    
    MSub, MHazard, MDehazard, MReflect, MLightScreen, MVitalThrow
};

const int MINPRIORITY = -7;
const int NORMPRIORITY = 0;
const int MAXPRIORITY = 7;

enum HoldItem
{
    HNoItem, HLeftovers, HChoiceBand, HChoiceScarf, HChoiceSpecs, HLightBall,
    HLifeOrb, HLightClay, HKingsRock, HFocusSash, HBlackSludge,
    HOranBerry, HSitrusBerry, HEjectPolicy, HRedCard,
    
    HVenusaurite, HCharizarditeX, HCharizarditeY, HBlastoisinite, HAlakazite, HGengarite, HKangaskhanite, HPinsirite, HGyaradosite, HAerodactylite, HMewtwoniteX, HMewtwoniteY, HAmpharosite, HScizorite, HHeracronite, HHoundoominite, HTyranitarite, HBlazikenite, HGardevoirite, HMawilite, HAggronite, HMedichamite, HManectite, HBannetite, HAbsolite, HGarchompite, HLucarionite, HAbomasite,
    
    HLatiasite, HLatiosite
};

const int NUMITEMS = 100;

// TODO: add all common battle items
// TODO: implement most of these items

// TODO: implement most abilities
enum PokeAbility
{
    PNoAbility, PLevitate, PSwiftSwim, PIntimidate, PHugePower, PStatic,
    PSereneGrace, PUnaware, PMagicBounce, PPressure, PSandStream, PMultiscale,
    PSynchronize, PClearBody, PDrizzle, PDrought, PAirLock, PStanceChange,
    PTorrent, PBlaze, POvergrow, PSwarm, PTechnician, PPoisonPoint,
    PSnowWarning, PAnticipation, PMoldBreaker, PPurePower
};

enum MoveType
{
    Physical, Special, Status
};

const int NUMMOVETYPES = 3;

enum ContestStat
{
    UnknownStat, Beauty, Cool, Smart, Tough, Cute
};

enum Generation
{
    I, II, III, IV, V, VI, VII, X
};

enum MoveTarget
{
    None, Self, Opponent, OpponentF, Both, All, Random
};

enum PokeStatus
{
    HealthyStatus, PoisonStatus, ToxicStatus, ParalyzeStatus, BurnStatus,
    FreezeStatus, SleepStatus, FaintStatus
};

const int NUMSTATUSES = 8;

enum VolatileStatus
{
    NoVStatus, ConfuseVStatus, AttractVStatus, CurseVStatus, BlockVStatus,
    EncoreVStatus, TormentVStatus, TauntVStatus, RampageVStatus, ProtectVStatus, ShieldVStatus, FocusVStatus, FlinchVStatus, FFlinchVStatus, SubVStatus
};

const int NUMVSTATUSES = 20;

enum Location
{
    GatewayColiseum, ShortGrass, TallGrass, Sand, StillWater, River, Ocean,
    Cave, DarkCave
};

enum Weather
{
    NoWeather, Sunny, Rain, Sandstorm, Hail
};

const int NUMWEATHERS = 5;

// TODO: implement terrain-type moves
enum Terrain
{
    NoTerrain, Grassy, Electric, Misty
};

// TODO: implement screen-type moves
enum Screen
{
    NoScreen, Reflect, LightScreen
};

const int MAXSCREENS = 2;

enum EntryHazard
{
    NoHazard, Spikes, ToxicSpikes, StealthRock
};

const int MAXHAZARDS = 3;

enum Gender
{
    Male, Female, Genderless, NoGender
};

enum BattleType
{
    SingleBattle, DoubleBattle, TripleBattle, RotationBattle, HoardBattle
};

// Auxiliary Function Declarations

void gyroscope(int& gyro, int& scope, Direction d);
int randInt(int lowest, int highest);
double typeMultiplier(Type type1, Type type2);
double typeMultiplier(Type type1, Type type2, Type type3);
double natureMultiplier(Nature nature, int stat);

#endif /* defined(__PokemonThrowdown__Constants__) */
