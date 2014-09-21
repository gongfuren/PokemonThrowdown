//
//  constants.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Constants__
#define __PokemonThrowdown__Constants__

// Note: This data file does not adhere to an 80 column limit!

// Global Constants

const int BACK = -1;

// TODO: organize use of constants

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

const int MAXNUMMOVES = 652;
const int MAXNUMPOKEMON = 801;

const int MAXTOTALMOVES = MAXNUMMOVES;
const int MAXTOTALPOKEMON = MAXNUMPOKEMON;
const int MAXTOTALTRAINERS = 100;

const int MAXTOTALBATTLES = 100;

const int MAXTYPES = 18 + 1 + 2;    // "Actual" types + NoType + Neutral/Light

const double EL0 = 0.00;
const double EL5 = 0.50;
const double EL1 = 1.00;
const double EL2 = 2.00;

// Attacking Type j, Defending Type i
const double typeArray[MAXTYPES][MAXTYPES] = {
    
 // NO    NRM   GRS   FIR   WTR   ELE   ICE   BUG   PSN   FGT   FLY   GRD   RCK   GHT   PSY   DRG   DRK   STL   FRY   NTL   LIT
    
    EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, // NO
    
    EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL5, EL0, EL1, EL1, EL1, EL5, EL1, EL1, EL1, // NRM
    
    EL1, EL1, EL5, EL5, EL2, EL1, EL1, EL1, EL5, EL1, EL5, EL2, EL2, EL1, EL1, EL5, EL1, EL5, EL1, EL1, EL1, // GRS
    
    EL1, EL1, EL2, EL5, EL5, EL1, EL2, EL2, EL1, EL1, EL1, EL1, EL5, EL1, EL1, EL5, EL1, EL2, EL1, EL1, EL1, // FIR
    
    EL1, EL1, EL5, EL2, EL5, EL1, EL1, EL1, EL1, EL1, EL1, EL2, EL2, EL1, EL1, EL5, EL1, EL1, EL1, EL1, EL1, // WTR
    
    EL1, EL1, EL5, EL1, EL2, EL5, EL1, EL1, EL1, EL1, EL2, EL0, EL1, EL1, EL1, EL5, EL1, EL1, EL1, EL1, EL1, // ELE
    
    EL1, EL1, EL2, EL5, EL5, EL1, EL5, EL1, EL1, EL1, EL2, EL2, EL1, EL1, EL1, EL2, EL1, EL5, EL1, EL1, EL1, // ICE
    
    EL1, EL1, EL2, EL5, EL1, EL1, EL1, EL1, EL5, EL5, EL5, EL5, EL1, EL5, EL2, EL1, EL2, EL5, EL5, EL1, EL1, // BUG
    
    EL1, EL1, EL2, EL1, EL1, EL1, EL1, EL5, EL5, EL5, EL1, EL5, EL5, EL1, EL1, EL1, EL1, EL0, EL2, EL1, EL1, // PSN
    
    EL1, EL2, EL1, EL1, EL1, EL1, EL2, EL5, EL5, EL1, EL5, EL1, EL2, EL0, EL5, EL1, EL2, EL2, EL5, EL1, EL1, // FGT
    
 // NO   NRM  GRS  FIR  WTR  ELE  ICE  BUG  PSN  FGT  FLY  GRD  RCK  GHT  PSY  DRG  DRK  STL  FRY  NTL  LIT
    
    EL1, EL1, EL2, EL1, EL1, EL5, EL1, EL2, EL1, EL2, EL1, EL1, EL5, EL1, EL1, EL1, EL1, EL5, EL1, EL1, EL1, // FLY
    
    EL1, EL1, EL5, EL2, EL1, EL2, EL1, EL5, EL2, EL1, EL0, EL1, EL2, EL1, EL1, EL1, EL1, EL2, EL1, EL1, EL1, // GRD
    
    EL1, EL1, EL1, EL2, EL1, EL1, EL2, EL2, EL1, EL5, EL2, EL5, EL1, EL1, EL1, EL1, EL1, EL5, EL1, EL1, EL1, // RCK
    
    EL1, EL0, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL2, EL2, EL1, EL5, EL1, EL1, EL1, EL5, // GHT
    
    EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL2, EL2, EL1, EL1, EL1, EL1, EL5, EL1, EL0, EL5, EL1, EL1, EL1, // PSY
    
    EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL2, EL1, EL5, EL0, EL1, EL1, // DRG
    
    EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL5, EL1, EL1, EL1, EL2, EL2, EL1, EL5, EL1, EL5, EL1, EL2, // DRK
    
    EL1, EL1, EL1, EL5, EL5, EL5, EL2, EL1, EL1, EL1, EL1, EL1, EL2, EL1, EL1, EL1, EL1, EL5, EL2, EL1, EL1, // STL
    
    EL1, EL1, EL1, EL5, EL1, EL1, EL1, EL1, EL5, EL2, EL1, EL1, EL1, EL1, EL1, EL2, EL2, EL5, EL1, EL1, EL1, // FRY
    
    EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, // NTL
    
    EL1, EL1, EL5, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL1, EL2, EL1, EL1, EL2, EL1, EL1, EL1, EL5  // LIT
};

const int NUMNATURES = 26;

const int MEGAFORM = 9;

const double natureArray[NUMNATURES][NUMSTATS-1] = {
//  ATT  DEF  SPA  SPD  SPE
    1.0, 1.0, 1.0, 1.0, 1.0, // NoNature
    1.0, 1.0, 1.0, 1.0, 1.0, // Hardy
    1.1, 0.9, 1.0, 1.0, 1.0, // Lonely
    1.1, 1.0, 1.0, 1.0, 0.9, // Brave
    1.1, 1.0, 0.9, 1.0, 1.0, // Adamant
    1.1, 1.0, 1.0, 0.9, 1.0, // Naughty
    1.0, 1.0, 1.0, 1.0, 1.0, // Docile
    0.9, 1.1, 1.0, 1.0, 1.0, // Bold
    1.0, 1.1, 1.0, 1.0, 0.9, // Relaxed
    1.0, 1.1, 0.9, 1.0, 1.0, // Impish
    1.0, 1.1, 1.0, 0.9, 1.0, // Lax
    1.0, 1.0, 1.0, 1.0, 1.0, // Serious
    0.9, 1.0, 1.0, 1.0, 1.1, // Timid
    1.0, 0.9, 1.0, 1.0, 1.1, // Hasty
    1.0, 1.0, 0.9, 1.0, 1.1, // Jolly
    1.0, 1.0, 1.0, 0.9, 1.1, // Naive
    1.0, 1.0, 1.0, 1.0, 1.0, // Bashful
    0.9, 1.0, 1.1, 1.0, 1.0, // Modest
    1.0, 0.9, 1.1, 1.0, 1.0, // Mild
    1.0, 1.0, 1.1, 1.0, 0.9, // Quiet
    1.0, 1.0, 1.1, 0.9, 1.0, // Rash
    1.0, 1.0, 1.0, 1.0, 1.0, // Quirky
    0.9, 1.0, 1.0, 1.1, 1.0, // Calm
    1.0, 0.9, 1.0, 1.1, 1.0, // Gentle
    1.0, 1.0, 1.0, 1.1, 0.9, // Sassy
    1.0, 1.0, 0.9, 1.1, 1.0 // Careful
};

const int NUMABILITIES = 35;

const int NUMTITLES = 28;

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
    NaughtyNature, DocileNature, BoldNature, RelaxedNature,
    ImpishNature, LaxNature, SeriousNature, TimidNature, HastyNature,
    JollyNature, NaiveNature, BashfulNature, ModestNature, MildNature,
    QuietNature, RashNature, QuirkyNature, CalmNature, GentleNature,
    SassyNature, CarefulNature
};

const int MINPRIORITY = -8;
const int NORMPRIORITY = 0;
const int MAXPRIORITY = 8;

const int NUMITEMS = 56;

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
    EncoreVStatus, TormentVStatus, TauntVStatus, RampageVStatus, ProtectVStatus, ShieldVStatus, FocusVStatus, FlinchVStatus, FFlinchVStatus, SubVStatus,
    FlyVStatus, DigVStatus, DiveVStatus, SolarVStatus, RchrgVStatus, SkyAttVStatus,
    RazorWVStatus, BashVStatus, PhantVStatus, ShadVStatus, BounceVStatus,
    GeoVStatus, FrzShckVStatus, IceBurnVStatus
};

const int NUMVSTATUSES = 30;

enum Location
{
    NoLocation, Coliseum, Plains, TallGrass, Beach, StillWater, River, Ocean,
    Cave, DarkCave, Indoors, Desert, Mountain, Volcano, Snow, Boreal, Forest, Jungle,
    Metal, Wood
};

const int NUMLOCATIONS = 20;

enum Weather
{
    NoWeather, Sunny, Rain, Sandstorm, Hail, Fog, Twilight, RandomWeather
};

const int NUMWEATHERS = 8;

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
    Male, Female, NoGender, Genderless
};

// TODO: organize and consolidate move effects
enum MoveEffect
{
    MNoEffect,
    
    // Status
    MPoison10, MPoison15, MPoison30, MPoison40, MToxic100, MBurn10, MBurn15, MBurn30, MFreeze10, MFreeze50, MParalyze10, MParalyze15, MParalyze30, MParalyze100, MConfuse10, MConfuse20, MConfuse100, MTri20, MConfuse, MAttract, MBurn, MSleep, MParalyze, MToxic, MPoison, MFlinch10, MFlinch20, MFlinch30, MFlinch100, MCrit100, MSleep50,
    
    // Stat Changes
    MLowerAtt, MLowerDef, MLowerSpA, MLowerSpD, MLowerSpe, MLowerAcc, MLowerEva, MLowerAcc100, MLowerAttDef, MLowerSpD10, MLowerSpD20, MLowerSpD40, MLowerSpD50, MLowerSpA100, MUpAtt, MUpDef, MUpSpA, MUpSpD, MUpSpe, MUpAcc, MUpEva, MUpDef10, MUpAtt100, MUpRnd, MUpAtt2, MUpDef2, MUpSpA2, MUpSpD2, MUpSpe2, MUpAcc2, MUpEva2, MUpSpA3, MUpDef3, MLowerAtt2, MLowerDef2, MLowerSpA2, MLowerSpD2, MLowerSpe2, MLowerAcc2, MLowerEva2, MLowerDefSpDUpAtt2SpA2Spe2, MLowerSpeUpAttDef, MUpSpASpD, MUpSpASpDSpe, MUpAttDefSpe, MUpAttSpe, MUpAttDef, MUpAttSpA, MUpDefSpD, MUpAttAcc, MUpAttSpe2, MUpAll, MUpSpD3,
    
    // Special 1
    MMoveFirst, MMoveFirst2, MHighCrit, MNeverMiss, MOHKO, MMultiHit, MDoubleHit, MRecharge, MOverheat, MAnnihilation, MCharge, MDamage20, MDamage40, MDamageLevel, MIgnoreDef100, MRampage, MProtect, MShield, MFocusPunch, MCounter, MRoar, MSuckerPunch, MSelfdestruct, MSolarbeam, MRazorwind, MSkullbash, MSkyAttack, MSkyDrop, MShadowForce, MFly, MDive, MDig, MPhantomForce, MSplash,
    
    // Stat Changes
    MLowerAttDefSelf, MLowerDefSpDSelf, MLowerDefSpDSpeSelf, MUpSpA50, MUpAll10,
    
    // HP Effects
    MHeal50, MHeal100, MDrain50, MDrain75, MRecoil25, MRecoil33, MRecoilStrug, MRecoilHalf,
    
    // Weather
    MRain, MSun, MHail, MSandstorm, MTrickRoom, MGravity, MTwilight,
    
    // Special 2
    MBind, MWrap, MFireSpin, MWhirlpool, MMagmaStorm, MSandTomb, MStomp, MMinimize, MJumpKick, MPayDay, MShockDef, MRage, MFuryCut, MTeleport, MDisable, MBatonPass, MTrap, MPartialTrap, MSub, MHazard, MDehazard, MReflect, MLightScreen, MVitalThrow, MFoul, MSplit, MTaunt, MStored
};

const int NUMTRACKS = 11;
enum musicTracks
{
    NoMusic, PBRGateway, BWTrainer, XYTrainer, RBYTrainer, RBYFinal, RBYChampion, RSEChampion, DPPtChampion, XYChampion, RSETrainer
};

const int NUMBATTLETYPES = 1;
const int NUMBATTLERULES = 1;
const int NUMBATTLELEVELS = 1;

enum BattleType
{
    SingleBattle, DoubleBattle, TripleBattle, RotationBattle, HoardBattle
};

enum BattleRule
{
    NoRestrictions
};

enum BattleLevel
{
    BLAny, BL100, BL50, BL5
};

const int NUMTRAINERS = 6;
const int MAXCTRAINERS = 10;

const int DF = 787;

const int MAXVOLUMELEVEL = 100;
const int MINVOLUMELEVEL = 0;
const int VOLUMEINCREMENTS = 10;

enum PokeAbility
{
    PNoAbility, PLevitate, PSwiftSwim, PIntimidate, PHugePower, PStatic,
    PSereneGrace, PUnaware, PMagicBounce, PPressure, PSandStream, PMultiscale,
    PSynchronize, PClearBody, PDrizzle, PDrought, PAirLock, PStanceChange,
    PTorrent, PBlaze, POvergrow, PSwarm, PTechnician, PPoisonPoint,
    PSnowWarning, PAnticipation, PMoldBreaker, PPurePower, PPrankster,
    PDefiant, PSpeedBoost, PDeathlyTouch, PSkillLink, PRunAway, POvercoat
};

#endif /* defined(__PokemonThrowdown__Constants__) */
