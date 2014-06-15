//
//  constants.h
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __pokemongame__Constants__
#define __pokemongame__Constants__

#include <string>
#include <list>
using namespace std;

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

const int STAND = -1;
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
const int NUMDIRS = 4;

const int HPSTAT = 0;
const int ATTSTAT = 1;
const int DEFSTAT = 2;
const int SPASTAT = 3;
const int SPDSTAT = 4;
const int SPESTAT = 5;
const int NUMSTATS = 6;

const int ACCSTAT = 6;
const int EVASTAT = 7;
const int CRITSTAT = 8;
const int NUMALLSTATS = 9;

const int MAXMOVES = 4;

const int NODECIS = 0;
const int FIGHT = 1;
const int BAG = 2;
const int SWITCH = 3;
const int RUN = 4;
const int MEGA = 5;

// Change based on battle style
// (Single, Double, Multi, Triple, Rotation, Hoard)
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

const int NOTYPE = 0;
const int NORMALTYPE = 1;
const int GRASSTYPE = 2;
const int FIRETYPE = 3;
const int WATERTYPE = 4;
const int ELECTRICTYPE = 5;
const int ICETYPE = 6;
const int BUGTYPE = 7;
const int POISONTYPE = 8;
const int FIGHTINGTYPE = 9;
const int FLYINGTYPE = 10;
const int GROUNDTYPE = 11;
const int ROCKTYPE = 12;
const int GHOSTTYPE = 13;
const int PSYCHICTYPE = 14;
const int DRAGONTYPE = 15;
const int DARKTYPE = 16;
const int STEELTYPE = 17;
const int FAIRYTYPE = 18;
const int NEUTRALTYPE = 19;
const int LIGHTTYPE = 20;

const int MAXTYPES = 18 + 1 + 2;    // "Actual" types + NoType + Neutral/Light

const string typeStrings[MAXTYPES] = {
    "No Type", "Normal", "Grass", "Fire", "Water", "Electric", "Ice", "Bug",
    "Poison", "Fighting", "Flying", "Ground", "Rock", "Ghost", "Psychic",
    "Dragon", "Dark", "Steel", "Fairy", "Neutral", "Light"
};

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

const int NONATURE = 0;
const int HARDY = 1;
const int LONELY = 2;
const int BRAVE = 3;
const int ADAMANT = 4;
const int NAUGHTY = 5;
const int BOLD = 6;
const int DOCILE = 7;
const int RELAXED = 8;
const int IMPISH = 9;
const int LAX = 10;
const int TIMID = 11;
const int HASTY = 12;
const int SERIOUS = 13;
const int JOLLY = 14;
const int NAIVE = 15;
const int MODEST = 16;
const int MILD = 17;
const int QUIET = 18;
const int BASHFUL = 19;
const int RASH = 20;
const int CALM = 21;
const int GENTLE = 22;
const int SASSY = 23;
const int CAREFUL = 24;
const int QUICK = 25;

const int NUMNATURES = 26;

const string natureStrings[NUMNATURES] = {
    "No Nature", "Hardy", "Lonely", "Brave", "Adamant", "Naughty", "Bold",
    "Docile", "Relaxed", "Impish", "Lax", "Timid", "Hasty", "Serious", "Jolly",
    "Naive", "Modest", "Mild", "Quiet", "Bashful", "Rash", "Calm", "Gentle",
    "Sassy", "Careful", "Quick"
};

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

const string statStrings[NUMALLSTATS] = {
    "HP", "Att", "Def", "SpA", "SpD", "Spe", "Acc", "Eva", "Crit"
};

const string statFullStrings[NUMALLSTATS] = {
    "HP", "Attack", "Defense", "Special Attack", "Special Defense", "Speed", "Accuracy", "Evasiveness", "Critical Hit Ratio"
};

const string statFLowerStrings[NUMALLSTATS] = {
};

const double STAT_N6 = 0.25;
const double STAT_N5 = 0.285;
const double STAT_N4 = 0.3333;
const double STAT_N3 = 0.40;
const double STAT_N2 = 0.50;
const double STAT_N1 = 0.6666;

const double STAT_B0 = 1.00;

const double STAT_P1 = 1.5;
const double STAT_P2 = 2.0;
const double STAT_P3 = 2.5;
const double STAT_P4 = 3.0;
const double STAT_P5 = 3.5;
const double STAT_P6 = 4.0;

const int HPBARLENGTH = 40;

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
    MHeal50, MDrain50, MDrain75,
    
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

const string itemStrings[NUMITEMS] = {
    "No Item", "Leftovers", "Choice Band", "Choice Scarf", "Choice Specs",
    "Light Ball", "Life Orb", "Light Clay", "King's Rock", "Focus Sash",
    "Black Sludge", "Oran Berry", "Sitrus Berry", "Eject Policy", "Red Card",
    
    "Venusaurite", "Charizardite X", "Charizardite Y", "Blastoisinite", "Alakazite", "Gengarite", "Kangaskhanite", "Pinsirite", "Gyaradosite", "Aerodactylite", "Mewtwonite X", "Mewtwonite Y", "Ampharosite", "Scizorite", "Heracronite", "Houndoominite", "Tyranitarite", "Blazikenite", "Gardevoirite", "Mawilite", "Aggronite", "Medichamite", "Manectite", "Bannetite", "Absolite", "Garchompite", "Lucarionite", "Abomasite",
    
    "Latiasite", "Latiosite"
};

enum PokeAbility
{
    PNoAbility, PLevitate, PSwiftSwim, PIntimidate, PHugePower, PStatic,
    PSereneGrace, PUnaware, PMagicBounce, PPressure, PSandStream, PMultiscale,
    PSynchronize, PClearBody, PDrizzle, PDrought, PAirLock, PStanceChange,
    PTorrent, PBlaze, POvergrow, PSwarm, PTechnician, PPoisonPoint,
    PSnowWarning, PAnticipation, PMoldBreaker, PPurePower
};

const string abilityStrings[NUMABILITIES] = {
    "No Ability", "Levitate", "Swift Swim", "Intimidate", "Huge Power",
    "Static", "Serene Grace", "Unaware", "MagicBounce", "Pressure",
    "Sand Stream", "Multiscale", "Synchronize", "Clear Body", "Drizzle",
    "Drought", "Air Lock", "Stance Change", "Torrent", "Blaze", "Overgrow",
    "Swarm", "Technician", "Poison Point", "Snow Warning", "Anticipation",
    "Mold Breaker", "Pure Power"
};

enum MoveType
{
    Physical, Special, Status
};

const int NUMMOVETYPES = 3;

const string moveTypeStrings[NUMMOVETYPES] = {
    "Physical", "Special", "Status"
};

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
    None, Self, Opponent, LongRange, Both, All, Random, TargetField, OwnSide, OpponentSide, BothSides
};

enum PokeStatus
{
    HealthyStatus, PoisonStatus, ToxicStatus, ParalyzeStatus, BurnStatus,
    FreezeStatus, SleepStatus, FaintStatus
};

const int NUMSTATUSES = 8;

const string statusStrings[NUMSTATUSES] = {
    "OK", "PSN", "PSN", "PRZ", "BRN", "FRZ", "SLP", "FNT"
};

const string statusFullStrings[NUMSTATUSES] = {
    "Healthy", "Poisoned", "Badly Poisoned", "Paralyzed", "Burned", "Frozen",
    "Asleep", "Fainted"
};

const string statusFSNoun[NUMSTATUSES] = {
    "No Status", "Poison", "Toxic", "Paralyze", "Burn", "Freeze", "Sleep", "Faint"
};

enum VolatileStatus
{
    NoVStatus, ConfuseVStatus, AttractVStatus, CurseVStatus, BlockVStatus,
    EncoreVStatus, TormentVStatus, TauntVStatus, RampageVStatus, ProtectVStatus, ShieldVStatus, FocusVStatus, FlinchVStatus, FFlinchVStatus, SubVStatus
};

const int NUMVSTATUSES = 20;

const string vstatusStrings[NUMVSTATUSES] = {
    "None", "Conf", "Attr", "Curs", "Blok", "Encr", "Trmt", "Taun", "Rmpg", "Prot", "Shld", "Fcus", "Flch", "Lfcs", "Subs"
};

const string vstatusFullStrings[NUMVSTATUSES] = {
    "None", "Confused", "Attract", "Cursed", "Blocked", "Encore", "Torment",
    "Taunt", "Rampaging", "Protect", "Shield", "Focusing", "Flinch", "Lost Focus", "Substitute"
};

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

const string weatherStrings[NUMWEATHERS] = {
    "No Weather", "Sunny", "Rain", "Sandstorm", "Hail"
};

const string weatherStartStrings[NUMWEATHERS] = {
    "", "The sunlight turned harsh.", "It started to rain.",
    "A sandstorm kicked up!", "It started to hail!"
};

const string weatherEndStrings[NUMWEATHERS] = {
    "", "The sunlight faded.", "The rain stopped.", "The sandstorm subsided.",
    "The hail stopped."
};

const string weatherContStrings[NUMWEATHERS] = {
    "", "The sunlight is harsh.", "Rain continues to fall.",
    "The sandstorm rages on.", "Hail continues to fall."
};

enum Terrain
{
    NoTerrain, Grassy, Electric, Misty
};

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
    Male, Female, Ungendered, NoGender
};

// Auxiliary Function Declarations

void gyroscope(int& gyro, int& scope, int d);
int randInt(int lowest, int highest);
int typeNumber(Type t);
double typeMultiplier(Type type1, Type type2);
double typeMultiplier(Type type1, Type type2, Type type3);
double natureMultiplier(Nature nature, int stat);
Nature returnNature(int whichNature);
int weatherNumber(Weather w);
Weather numberWeather(int n);

#endif /* defined(__pokemongame__Constants__) */
