//
//  Pokemon.cpp
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Pokemon.h"
#include "pokedata.h"
#include "Trainer.h"
#include "Battle.h"
#include "constants.h"
#include "strings.h"
#include "Item.h"

#include <iostream>
#include <string>
using namespace std;

Pokemon::Pokemon(pokedata h, Trainer* trainer, int wp)
: m_trainer(trainer)
{
    m_name = h.name;
    m_type1 = h.type1;
    m_type2 = h.type2;
    m_status = HealthyStatus;
    m_gender = h.gender;
    m_intendedMove = 0;
    m_level = h.level;
    m_nature = (h.nature == NoNature)
    ? static_cast<Nature>(randInt(HardyNature, NUMNATURES-1)) : h.nature;
    m_ability = h.ability[0];
    m_item = new Item(h.item);
    m_description = h.description;
    m_sleepTurns = 0;
    m_toxicTurns = 0;
    m_rampageTurns = 0;
    m_tauntTurns = 0;
    m_ID = h.ID;
    m_form = 0;
    m_turnsOut = -1;
    m_fainted = false;
    m_locked = NULL;
    
    for (int i = HPStat; i < NUMSTATS; i++)
    {
        int adder = (i == HPStat) ? 10 + m_level : 5;
        double nature = (i == HPStat) ? 1.0 : natureMultiplier(m_nature, i-1);
        m_IVs[i] = (h.IVs[i] == -1) ? randInt(0, 31)
        : h.IVs[i];
        m_EVs[i] = (h.EVs[i] == -1) ? randInt(0, 85)
        : h.EVs[i];
        m_bStats[i] = ((2 * h.stats[i] + m_IVs[i] + m_EVs[i]
                        / 4) * m_level / 100 + adder) * nature;
    }
    
    m_statsStatus[HPStat] = m_bStats[HPStat];
    
    for (int i = AttStat; i < NUMALLSTATS; i++)
    {
        m_statsStatus[i] = 0;
    }
    
    for (int i = 0; i < MAXMOVES; i++)
    {
        int ic = getTrainer()->getBattle()->getNumPlayers();
        
        if (getTrainer()->getBattle()->getPreMoveIDs(ic, wp, i) != -1)
            m_moves[i] = new Move(getTrainer()->getBattle()->getPreMoveIDs(ic, wp, i), this);
        else
        {
            if (h.moveIDs[i] != -1)
                m_moves[i] = new Move(h.moveIDs[i], this);
            else
                m_moves[i] = NULL;
        }
    }
    
    if (m_gender == NoGender)
        m_gender = static_cast<Gender>(randInt(0, 1));
}

Pokemon::~Pokemon()
{
    for (int i = 0; i < MAXMOVES; i++)
        delete m_moves[i];
}

void Pokemon::transform(int pokemonID)
{
    pokedata me = pokelib[pokemonID];
    
    m_name = me.name;
    m_type1 = me.type1;
    m_type2 = me.type2;
    m_ability = me.ability[0];
    
    for (int i = AttStat; i < NUMSTATS; i++)
    {
        int adder = 5;
        m_bStats[i] = ((2 * me.stats[i] + m_IVs[i] + m_EVs[i] / 4) * m_level
                       / 100 + adder) * natureMultiplier(m_nature, i-1);
    }
}

int Pokemon::getForm() const
{
    return m_form;
}

bool Pokemon::hasCompatMegaStone() const
{
    bool hci = false;
    int pind = -1;
    int ms = static_cast<int>(m_item->getID() - HVenusaurite);
    
    for (int i = 722; i <= 753; i++)
    {
        if (pokelib[i].ID == m_ID)
            pind = i;
    }
    
    if (ms >= 0 && ms == pind - 722)
        hci = true;
    
    return hci;
}

int Pokemon::getSleepTurns() const
{
    return m_sleepTurns;
}

int Pokemon::getRampageTurns() const
{
    return m_rampageTurns;
}

void Pokemon::setRampageTurns(int turns)
{
    m_rampageTurns = turns;
}

Trainer* Pokemon::getTrainer() const
{
    return m_trainer;
}

string Pokemon::getName() const
{
    return m_name;
}

void Pokemon::clearVolatiles()
{
    // Reset turns out counter
    m_turnsOut = -1;
    
    // Undo stat changes
    for (int i = 1; i < NUMALLSTATS; i++)
    {
        restoreStat(i);
    }
    
    // Reset Toxic counter
    if (getStatus() == ToxicStatus)
        setToxicTurns(0);
    
    // Reset Sleep counter
    if (getStatus() == SleepStatus)
        setSleepTurns(randInt(1, 3));
    
    // Clear volatile statuses
    removeVStatuses();
    
    // Undo volatile transformations
    if (m_ID == 681)
        // Aegislash
    {
        if (m_form == 1)
            transform(681);
    }
    
    // Reset Move history
    while (!m_moveHistory.empty())
        m_moveHistory.pop();
}

Type Pokemon::getType1() const
{
    return m_type1;
}

Type Pokemon::getType2() const
{
    return m_type2;
}

PokeStatus Pokemon::getStatus() const
{
    return m_status;
}

double Pokemon::getStats(int whichStat) const
{
    if (whichStat == HPStat)
        return m_statsStatus[whichStat];
    else if (whichStat == AccStat || whichStat == EvaStat)
        return statEMultiplier(m_statsStatus[whichStat]);
    else
        return m_bStats[whichStat] * statAMultiplier(m_statsStatus[whichStat]);
}

int Pokemon::getBStats(int whichStat) const
{
    return m_bStats[whichStat];
}

int Pokemon::getStatsStatus(int whichStat) const
{
    return m_statsStatus[whichStat];
}

Move* Pokemon::getMove(int whichMove) const
{
    return m_moves[whichMove];
}

Gender Pokemon::getGender() const
{
    return m_gender;
}

int Pokemon::getLevel() const
{
    return m_level;
}

Nature Pokemon::getNature() const
{
    return m_nature;
}

string Pokemon::getDescription() const
{
    return m_description;
}

PokeAbility Pokemon::getAbility() const
{
    return m_ability;
}

int Pokemon::getToxicTurns() const
{
    return m_toxicTurns;
}

void Pokemon::setToxicTurns(int turns)
{
    m_toxicTurns = turns;
}

void Pokemon::setSleepTurns(int turns)
{
    m_sleepTurns = turns;
}

void Pokemon::flashAbility() const
{
    cout << m_name << "'s " << abilityStrings[m_ability] << ":" << endl;
}

void Pokemon::tick()
{
    m_turnsOut++;
}

void Pokemon::castAbility()
{
    if (m_turnsOut != -1)
        return;
    
    Pokemon* opponent;
    Trainer* actor;
    
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        actor = getTrainer()->getBattle()->getParticipants(i);
        opponent = actor->getPokemon();
        
        if (opponent == this)
            // This loop deals with ability effects on other Pokemon
            continue;
        
        if (getAbility() == PIntimidate)
        {
            flashAbility();
            opponent->decreaseStat(AttStat, false);
        }
        
        if (getAbility() == PDrizzle
            && getTrainer()->getBattle()->getWeather() != Rain)
        {
            flashAbility();
            getTrainer()->getBattle()->getField()->initializeWeather(Rain);
        }
        
        if (getAbility() == PDrought
            && getTrainer()->getBattle()->getWeather() != Sunny)
        {
            flashAbility();
            getTrainer()->getBattle()->getField()->initializeWeather(Sunny);
        }
        
        if (getAbility() == PSandStream
            && getTrainer()->getBattle()->getWeather() != Sandstorm)
        {
            flashAbility();
            getTrainer()->getBattle()->getField()->
            initializeWeather(Sandstorm);
        }
        
        if (getAbility() == PSnowWarning
            && getTrainer()->getBattle()->getWeather() != Hail)
        {
            flashAbility();
            getTrainer()->getBattle()->getField()->initializeWeather(Hail);
        }
        
        if (getAbility() == PPressure)
        {
            flashAbility();
            cout << getName() << " " << "is exerting its Pressure!" << endl;
        }
    }
    
    m_turnsOut = 0;
}

bool Pokemon::isFainted() const
{
    return m_fainted;
}

bool Pokemon::canMegaEvolve() const
{
    return (hasCompatMegaStone() && getForm() == 0 && !getTrainer()->getUsedMega());
}

void Pokemon::setFainted()
{
    m_statsStatus[HPStat] = 0;
    
    m_fainted = true;
    setStatus(FaintStatus);
}

void Pokemon::lowerHP(int howMuch)
{
    m_statsStatus[HPStat] -= howMuch;
    
    if (m_statsStatus[HPStat] <= 0)
    {
        m_statsStatus[HPStat] = 0;
    }
}

bool Pokemon::hasMaxHP() const
{
    return (m_statsStatus[HPStat] == m_bStats[HPStat]);
}

bool Pokemon::increaseHP(int howMuch)
{
    if (hasMaxHP())
        return false;
    
    m_statsStatus[HPStat] += howMuch;
    
    if (m_statsStatus[HPStat] >= m_bStats[HPStat])
    {
        m_statsStatus[HPStat] = m_bStats[HPStat];
    }
    
    return true;
}

void Pokemon::protectDialogue() const
{
    Trainer* trainer = getTrainer();

    cout << trainer->getTitleName() << "'s "
    << m_name << " " << "protected itself!" << endl;
}

void Pokemon::avoidDialogue() const
{
    Trainer* trainer = getTrainer();
    
    cout << trainer->getTitleName() << "'s "
    << getName() << " " << "avoided the attack!" << endl;
}

bool Pokemon::decreaseStat(int whichStat, bool silent)
{
    bool normalExecution = true;
    
    if (!silent && m_ability == PClearBody)
        // Clear Body cancellation
    {
        normalExecution = false;
        
        flashAbility();
        
        cout << getTrainer()->getTitleName()
        << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
        << "was not lowered!" << endl;
    }
    
    if (normalExecution)
    {
        if (!silent && m_statsStatus[whichStat] <= -6)
        {
            cout << getTrainer()->getTitleName()
            << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
            << "can't go any lower!" << endl;
        }
        else
        {
            if (!silent)
            {
                cout << getTrainer()->getTitle() << " "
                << getTrainer()->getName() << "'s " << m_name << "'s "
                << statFullStrings[whichStat] << " " << "fell!" << endl;
            }
            
            m_statsStatus[whichStat]--;
        }
    }
    
    return normalExecution;
}

bool Pokemon::decreaseStat(int whichStat, int levels)
{
    if (levels == 1)
    {
        return decreaseStat(whichStat, false);
    }
    
    bool min = (levels == 6) ? true : false;
    
    if (m_statsStatus[whichStat] <= -6)
        cout << getTrainer()->getTitleName()
        << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
        << "can't go any lower!" << endl;
    else
    {
        if (decreaseStat(whichStat, true))
        {
            levels--;
            int decrease;
            
            for (decrease = 0; levels > 0 && m_statsStatus[whichStat] >= -6;
                 levels--)
            {
                if (decreaseStat(whichStat, true))
                    decrease++;
            }
            
            if (min)
                cout << getTrainer()->getTitle() << " "
                << getTrainer()->getName() << "'s " << m_name << "'s "
                << statFullStrings[whichStat] << " " << "was minimized!" << endl;
            else
            {
                switch (decrease)
                {
                    default:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << "fell!"
                        << endl;
                        break;
                    case 1:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << "harshly fell!"
                        << endl;
                        break;
                    case 2:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << "fell dramatically!"
                        << endl;
                        break;
                }
            }
        }
    }
    
    return true;
}

bool Pokemon::increaseStat(int whichStat, bool silent)
{
    if (m_statsStatus[whichStat] >= 6)
    {
        if (!silent)
            cout << getTrainer()->getTitleName()
            << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
            << "can't go any higher!" << endl;
        
        return true;
    }
    
    if (!silent)
        cout << getTrainer()->getTitleName()
        << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
        << "increased!" << endl;
    
    m_statsStatus[whichStat]++;
    
    return true;
}

bool Pokemon::increaseStat(int whichStat, int levels)
{
    if (levels == 1)
    {
        return increaseStat(whichStat, false);
    }
    
    bool max = (levels == 6) ? true : false;
    
    if (m_statsStatus[whichStat] >= 6)
        cout << getTrainer()->getTitleName()
        << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
        << "can't go any higher!" << endl;
    else
    {
        if (increaseStat(whichStat, true))
        {
            levels--;
            int increase;
            
            for (increase = 0; levels > 0 && m_statsStatus[whichStat] <= 6;
                 levels--)
            {
                if (increaseStat(whichStat, true))
                    increase++;
            }
            
            if (max)
                cout << getTrainer()->getTitle() << " "
                << getTrainer()->getName() << "'s " << m_name << " "
                << "maximized its" << " " << statFullStrings[whichStat] << "!"
                << endl;
            else
            {
                switch (increase)
                {
                    default:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << "increased!"
                        << endl;
                        break;
                    case 1:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << "sharply increased!"
                        << endl;
                        break;
                    case 2:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << "drastically increased!"
                        << endl;
                        break;
                }
            }
        }
    }
    
    return true;
}

void Pokemon::restoreStat(int whichStat)
{
    if (m_statsStatus[whichStat] == 0)
        return;
    
    if (m_statsStatus[whichStat] < 0)
        while (m_statsStatus[whichStat] != 0)
            increaseStat(whichStat, true);
    
    if (m_statsStatus[whichStat] > 0)
        while (m_statsStatus[whichStat] != 0)
            decreaseStat(whichStat, true);
}

double Pokemon::statAMultiplier(int statLevel) const
{
    return STAT_A[6 + statLevel];
}

double Pokemon::statEMultiplier(int statLevel) const
{
    return STAT_E[6 + statLevel];
}

int Pokemon::getIntendedMove() const
{
    return m_intendedMove;
}

Item* Pokemon::getItem() const
{
    return m_item;
}

bool Pokemon::passThroughStatus()
{
    bool pass = true;
    int thru = randInt(0,99);
    
    if (m_status != HealthyStatus)
        cout << getTrainer()->getTitleName()
        << "'s ";
    
    if (m_status == ParalyzeStatus && thru < 25)
    {
        cout << m_name << " " << "is paralyzed! It can't move!" << endl;
        pass = false;
    }
    else if (m_status == SleepStatus)
    {
        if (m_sleepTurns-- > 0)
        {
            cout << m_name << " " << "is fast asleep." << endl;
            pass = false;
        }
        else
        {
            cout << m_name << " " << "woke up!" << endl;
            m_status = HealthyStatus;
            pass = true;
        }
    }
    else if (m_status == FreezeStatus)
    {
        if (thru < 80)
        {
            cout << m_name << " " << "is frozen solid!" << endl;
            pass = false;
        }
        else
        {
            cout << m_name << " " << "thawed out!" << endl;
            m_status = HealthyStatus;
            pass = true;
        }
    }
    else if (hasVStatus(FlinchVStatus))
    {
        cout << m_name << " " << "flinched!" << endl;
        pass = false;
    }
    else if (hasVStatus(FFlinchVStatus))
    {
        cout << m_name << " " << "lost its focus and couldn't move!" << endl;
        pass = false;
    }
    else    // NoStatus
        pass = true;
    
    thru = randInt(0,999);
    
    if (hasVStatus(ConfuseVStatus))
    {
        int so = randInt(0,3);
        bool snapOut = (so == 0);
        
        if (snapOut)
        {
            cout << m_name << " " << "snapped out of its confusion!" << endl;
            removeVStatus(ConfuseVStatus);
        }
        else
        {
            cout << m_name << " " << "is confused!" << endl;
            
            if (thru < 500)
            {
                cout << m_name << " " << "hurt itself in its confusion!" << endl;
                
                int pureDamage = 40;
                int attackMultiplier = 1.0;
                if (getAbility() == PHugePower || getAbility() == PPurePower)
                    attackMultiplier = 2.0;
                int spOrNot
                = static_cast<double>(getStats(AttStat) * attackMultiplier)
                / static_cast<double>(getStats(DefStat));
                double damage = (((2.0 * getLevel() + 10.0) / 250.0) *
                                 (spOrNot) * pureDamage + 2.0);
                
                lowerHP(damage);
                
                pass = false;
            }
        }
    }
    
    return pass;
}

void Pokemon::formChange(int form)
{
    if (form == MEGAFORM)
        // Mega Evolution
    {
        cout << m_name << "'s " << itemStrings[m_item->getID()] << " "
        << "is reacting to" << " " << getTrainer()->getName() << "'s "
        << "Mega Ring!" << endl;
        
        cout << m_name << " " << "has Mega Evolved into Mega" << " " << m_name << "!"
        << endl;
        
        transform(m_item->getID() - HVenusaurite + 722);
        
        getTrainer()->setUsedMega();
    }
    else if (m_ID == 681)
        // Aegislash
    {
        flashAbility();
        
        cout << "Changed to" << " ";
        
        if (m_form == 0)
            // Shield to Blade
        {
            transform(762);
            
            cout <<  "Blade";
        }
        else
            // Blade to Shield
        {
            transform(681);
            
            cout << "Shield";
        }
        
        cout << " " << "Forme!" << endl;
    }
    
    m_form = form;
}

void Pokemon::megaEvolve()
{
    formChange(MEGAFORM);
    m_turnsOut = -1;
}

void Pokemon::addVStatus(VolatileStatus vstatus)
{
    m_vstatuses.push_back(vstatus);
}

bool Pokemon::hasVStatus(VolatileStatus vstatus)
{
    return listContains(m_vstatuses, vstatus);
}

void Pokemon::removeVStatus(VolatileStatus vstatus)
{
    m_vstatuses.remove(vstatus);
}

bool Pokemon::setStatus(PokeStatus status, bool rest)
{
    if (status != FaintStatus && getStatus() != HealthyStatus)
        return false;
    
    switch (status)
    {
        case FaintStatus:
            break;
        case FreezeStatus:
            if ((getType1() == IceType || getType2() == IceType) ||
                getTrainer()->getBattle()->getWeather() == Sunny)
                // Ice types cannot be frozen
                // No freezing occurs in sunny weather
                return false;
            break;
        case ParalyzeStatus:
            if (getType1() == ElectricType || getType2() == ElectricType)
                // Electric types cannot be paralyzed
                return false;
            break;
        case BurnStatus:
            if (getType1() == FireType || getType2() == FireType)
                // Fire types cannot be burned
                return false;
            break;
        case PoisonStatus:
        case ToxicStatus:
            if (getType1() == PoisonType || getType2() == PoisonType ||
                getType1() == SteelType || getType2() == SteelType)
                // Poison and Steel types cannot be poisoned
                return false;
            break;
        case SleepStatus:
            break;
        default:
            break;
    }
    
    m_status = status;
    
    if (!rest)
        cout << getTrainer()->getTitleName()
        << "'s " << m_name << " " << statusStartStrings[status] << endl;
    
    if (status == SleepStatus)
    {
        if (!rest)
            m_sleepTurns = randInt(1, 3);
        else
            m_sleepTurns = 2;
    }
    
    return true;
}

void Pokemon::setIntendedMove(int choice)
{
    m_intendedMove = choice;
}

void Pokemon::checkFaint()
{
    if (!isFainted() && getStats(HPStat) == 0)
        setFainted();
}

bool Pokemon::executeMove(Pokemon* target, Move* move)
{
    int intendedMove = getIntendedMove();
    Battle* battle = getTrainer()->getBattle();
    Weather weather;
    bool moveHits, changeForm, rerun;
    int moveAccuracy, whatForm;
    VolatileStatus vs;
    
    if (move == NULL)
    {
        move = getMove(intendedMove);
    }
    
    if (isFainted())
        return false;
    
    weather = battle->getWeather();
    
    if (hasVStatus(TauntVStatus))
    {
        if (move->getMoveType() == Status)
        {
            cout << getName() << " can't use " << move->getName() << " after"
            << " the taunt!" << endl;
            return false;
        }
    }
    
    if (getAbility() == PStanceChange)
    {
        changeForm = false;
        
        if (getForm() == 0)
        {
            whatForm = 1;
            
            if (move->getMoveType() != Status)
                changeForm = true;
        }
        else
        {
            whatForm = 0;
            
            if (move->getID() == 588)
                changeForm = true;
        }
        
        if (changeForm)
            formChange(whatForm);
    }
    
    if (move->getEffect() == MCharge)
    {
        rerun = false;
        
        do
        {
            switch (move->getID())
            {
                case 76: // Solar Beam
                    vs = SolarVStatus;
                    break;
                case 19: // Fly
                    vs = FlyVStatus;
                    break;
                case 91: // Dig
                    vs = DigVStatus;
                    break;
                case 291: // Dive
                    vs = DiveVStatus;
                    break;
                case 13: // Razor Wind
                    vs = RazorWVStatus;
                    break;
                case 143: // Sky Attack
                    vs = SkyAttVStatus;
                    break;
                case 130: // Skull Bash
                    vs = BashVStatus;
                    break;
                case 566: // Phantom Force
                    vs = PhantVStatus;
                    break;
                case 467: // Shadow Force
                    vs = ShadVStatus;
                    break;
                case 340: // Bounce
                    vs = BounceVStatus;
                    break;
                case 601: // Geomancy
                    vs = GeoVStatus;
                    break;
                case 553: // Freeze Shock
                    vs = FrzShckVStatus;
                    break;
                case 554: // Ice Burn
                    vs = IceBurnVStatus;
                    break;
                default:
                    vs = SolarVStatus;
                    break;
            }
            
            if (!hasVStatus(vs))
            {
                cout << getTrainer()->getTitleName() << "'s " << getName() << " ";
                
                switch (move->getID())
                {
                    case 76: // Solar Beam
                        cout << "absorbed light!";
                        if (weather == Sunny)
                            rerun = true;
                        break;
                    case 19: // Fly
                        cout << "flew up high!";
                        break;
                    case 91: // Dig
                        cout << "went underground!";
                        break;
                    case 291: // Dive
                        cout << "dove underwater!";
                        break;
                    case 13: // Razor Wind
                        cout << "whipped up a whirlwind!";
                        break;
                    case 143: // Sky Attack
                        cout << "became cloaked in a harsh light!";
                        break;
                    case 130: // Skull Bash
                        cout << "tucked in its head!";
                        break;
                    case 566: // Phantom Force
                    case 467: // Shadow Force
                        cout << "vanished instantly!";
                        break;
                    case 340: // Bounce
                        cout << "bounced up high!";
                        break;
                    case 601: // Geomancy
                    case 553: // Freeze Shock
                    case 554: // Ice Burn
                        cout << "is absorbing power!";
                        break;
                    default:
                        break;
                }
                
                cout << endl;
                
                addVStatus(vs);
                lockMove(getMove(getIntendedMove()));
                
                if (!rerun)
                    return false;
            }
            else
            {
                removeVStatus(vs);
                unlockMove();
                rerun = false;
            }
        }
        while (rerun);
    }
    
    cout << getTrainer()->getTitleName() << "'s "
    << getName() << " " << "used" << " " << move->getName() << "!"
    << endl;
    
    moveAccuracy = move->getAccuracy();
    
    if (move->getID() == 87 || move->getID() == 542 || move->getID() == 59)
        // Weather-dependent accuracy adjustments for Thunder, Hurricane,
        // Blizzard
    {
        if (weather == Sunny)
            moveAccuracy = 50;
        else if ((weather == Rain && (move->getID() == 87
                                      || move->getID() == 542))
                 || (weather == Hail && move->getID() == 59))
            moveAccuracy = 100;
    }
    
    if (move->getEffect() == MNeverMiss)
        // Never miss
    {
        moveHits = true;
    }
    else if (target->hasVStatus(FlyVStatus) || target->hasVStatus(DigVStatus)
             || target->hasVStatus(ShadVStatus)
             || target->hasVStatus(PhantVStatus)
             || target->hasVStatus(DiveVStatus)
             || target->hasVStatus(BounceVStatus))
    {
        moveHits = false;
        
        if (target->hasVStatus(FlyVStatus) &&
            // Thunder, Twister, Gust, Sky Uppercut
            (move->getID() == 87 || move->getID() == 239
             || move->getID() == 16))
            moveHits = true;
        
        if (target->hasVStatus(DigVStatus) &&
            // Earthquake, Magnitude
            (move->getID() == 89 || move->getID() == 222))
            moveHits = true;
        
        // TODO (unfinished)
    }
    else
        // Normal accuracy calculation
    {
        double a = getStats(AccStat);
        double b = target->getStats(EvaStat);
        double c = moveAccuracy * (a / b);
        c += 0.5;   // round
        
        moveAccuracy = c;
        
        moveHits = (randInt(0, 99) < moveAccuracy);
    }
    
    if (target->hasVStatus(ProtectVStatus))
        moveHits = false;
    
    if (move->determineFailure(target))
        // Move failed
    {
        cout << "But it failed!" << endl;
        
        return false;
    }
    
    if (move->getTarget() == Self || move->getTarget() == None)
        // Move used on self or other
    {
        if (move->getMoveType() == Status)
            // Status move
            applyStatus(target, getMove(intendedMove));
        else
            // Attack
            applyAttack(target, getMove(intendedMove));
    }
    else
        // Targeting pokemon other than self
    {
        if (target == NULL || target->isFainted())
        {
            cout << "But there was no target!" << endl;
            
            return false;
        }
        
        if (!moveHits)
            // Move missed or was protected against
        {
            if (target->hasVStatus(ProtectVStatus))
                target->protectDialogue();
            else
                target->avoidDialogue();
            
            return false;
        }
        else if (move->getMoveType() == Status)
            // Status move
            applyStatus(target, getMove(intendedMove));
        else
            // Attack
            applyAttack(target, getMove(intendedMove));
    }
    
    applySideEffects(getMove(intendedMove));
    
    battle->displayState(false);
    battle->checkFaint();
    
    // Record move
    recordMove(true);
    
    return true;
}

Slot* Pokemon::getSlot() const
{
    return m_slot;
}

void Pokemon::removeShortStatus()
{
    if (hasVStatus(ProtectVStatus))
        removeVStatus(ProtectVStatus);
    if (hasVStatus(ShieldVStatus))
        removeVStatus(ShieldVStatus);
    if (hasVStatus(FFlinchVStatus))
        removeVStatus(FFlinchVStatus);
    if (hasVStatus(FlinchVStatus))
        removeVStatus(FlinchVStatus);
}

Move* Pokemon::lastTurnsMove() const
{
    return moveUsedLast(1);
}

Move* Pokemon::moveUsedLast(int turnsAgo) const
{
    Move* move = NULL;
    stack<Move*> movestack = m_moveHistory;
    
    while (!movestack.empty() && --turnsAgo > 0)
    {
        movestack.pop();
    }
    
    if (!movestack.empty())
    {
        move = movestack.top();
    }
    
    return move;
}

void Pokemon::recordMove(bool successful)
{
    Move* move = getMove(getIntendedMove());
    
    if (successful)
        m_moveHistory.push(move);
    else
        m_moveHistory.push(NULL);
}

bool Pokemon::usedProtect(int turnsAgo) const
{
    return moveUsedLast(turnsAgo) != NULL &&
    (moveUsedLast(turnsAgo)->getEffect() == MProtect ||
     moveUsedLast(turnsAgo)->getEffect() == MShield);
}

int Pokemon::getID() const
{
    return m_ID;
}

bool Pokemon::applyStatus(Pokemon* target, Move* move)
{
    Pokemon* pokemon = this;
    MoveEffect me = move->getEffect();
    Field* field = getTrainer()->getBattle()->getField();
    Weather weather = field->getWeather();
    int healAmount, shp, thp, php;
    
    healAmount = 0;
    int sc[NUMALLSTATS] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    
    if (me == MHeal50)
        // Calculate heal amount for Healing moves
    {
        healAmount = pokemon->getBStats(HPStat) / 2;
        
        if (move->getID() >= 234 && move->getID() <= 236)
        {
            // Weather-influenced healing move
            if (weather == Sunny)
                healAmount = (2 * pokemon->getBStats(HPStat)) / 3;
            else if (weather != NoWeather)
                healAmount = pokemon->getBStats(HPStat) / 4;
        }
    }
    else if (me == MHeal100)
        // Heal amount and sleep effect for Rest
    {
        healAmount = pokemon->getBStats(HPStat);
    }
    
    switch (me)
    {
        case MHeal50:
            cout << target->getTrainer()->getTitleName() << "'s "
            << target->getName();
            if (target->increaseHP(healAmount))
                cout << "'s "<< "HP was restored!";
            else
                cout << "'s " << "HP can't go any higher!";
            cout << endl;
            break;
        case MHeal100:
            if (target->increaseHP(healAmount))
            {
                cout << target->getTrainer()->getTitleName() << "'s "
                << target->getName() << " "
                << "went to sleep and became healthy!" << endl;
                
                pokemon->removeVStatuses();
                pokemon->removeStatus();
                pokemon->setStatus(SleepStatus, true);
            }
            else
                cout << target->getTrainer()->getTitleName() << "'s "
                << target->getName() << "'s "
                << "HP can't go any higher!" << endl;
            break;
        case MSplit:
            shp = target->getStatsStatus(HPStat);
            thp = getStatsStatus(HPStat);
            php = (shp + thp) / 2;
            if (shp >= php)
            {
                target->lowerHP(shp - php);
                increaseHP(shp - php);
            }
            else
            {
                target->increaseHP(thp - php);
                lowerHP(thp - php);
            }
            cout << "The battlers shared their pain!" << endl;
            break;
        case MTaunt:
            if (target->hasVStatus(TauntVStatus))
                return false;
            cout << target->getName() << " fell for the taunt!" << endl;
            target->addVStatus(TauntVStatus);
            target->m_tauntTurns = 3;
            break;
        case MLowerAtt:
            sc[AttStat] = -1;
            break;
        case MLowerAtt2:
            sc[AttStat] = -2;
            break;
        case MUpAtt:
            sc[AttStat] = 1;
            break;
        case MUpAtt2:
            sc[AttStat] = 2;
            break;
        case MLowerDef:
            sc[DefStat] = -1;
            break;
        case MLowerDef2:
            sc[DefStat] = -2;
            break;
        case MUpDef:
            sc[DefStat] = 1;
            break;
        case MUpDef2:
            sc[DefStat] = 2;
            break;
        case MLowerSpA:
            sc[SpAStat] = -1;
            break;
        case MLowerSpA2:
            sc[SpAStat] = -2;
            break;
        case MUpSpA:
            sc[SpAStat] = 1;
            break;
        case MUpSpA2:
            sc[SpAStat] = 2;
            break;
        case MLowerSpD:
            sc[SpDStat] = -1;
            break;
        case MLowerSpD2:
            sc[SpDStat] = -2;
            break;
        case MUpSpD:
            sc[SpDStat] = 1;
            break;
        case MUpSpD2:
            sc[SpDStat] = 2;
            break;
        case MLowerSpe:
            sc[SpeStat] = -1;
            break;
        case MLowerSpe2:
            sc[SpeStat] = -2;
            break;
        case MUpSpe:
            sc[SpeStat] = 1;
            break;
        case MUpSpe2:
            sc[SpeStat] = 2;
            break;
        case MUpSpASpD:
            sc[SpAStat] = 1;
            sc[SpDStat] = 1;
            break;
        case MUpAttDef:
            sc[AttStat] = 1;
            sc[DefStat] = 1;
            break;
        case MUpAttSpA:
            sc[AttStat] = 1;
            sc[SpAStat] = 1;
            break;
        case MUpDefSpD:
            sc[DefStat] = 1;
            sc[SpDStat] = 1;
            break;
        case MUpAttSpe:
            sc[AttStat] = 1;
            sc[SpeStat] = 1;
            break;
        case MUpSpASpDSpe:
            sc[SpAStat] = 1;
            sc[SpDStat] = 1;
            sc[SpeStat] = 1;
            break;
        case MUpAll:
            for (int i = AttStat; i < NUMSTATS; i++)
                sc[i] = 1;
            break;
        case MSun:
            if (weather != Sunny)
                field->initializeWeather(Sunny);
            break;
        case MRain:
            if (weather != Rain)
                field->initializeWeather(Rain);
            break;
        case MSandstorm:
            if (weather != Sandstorm)
                field->initializeWeather(Sandstorm);
            break;
        case MHail:
            if (weather != Hail)
                field->initializeWeather(Hail);
            break;
        case MProtect:
            target->addVStatus(ProtectVStatus);
            target->protectDialogue();
            break;
        case MShield:
            target->addVStatus(ShieldVStatus);
            target->protectDialogue();
            break;
        case MBurn:
            if (target->setStatus(BurnStatus))
                ;
            break;
        case MSleep:
            if (target->setStatus(SleepStatus))
                ;
            break;
        case MPoison:
            if (target->setStatus(PoisonStatus))
                ;
            break;
        case MToxic:
            if (target->setStatus(ToxicStatus))
                ;
            break;
        case MParalyze:
            if (target->setStatus(ParalyzeStatus))
                ;
            break;
        default:
            break;
    }
    
    for (int i = AttStat; i < NUMALLSTATS; i++)
    {
        if (sc[i] < 0)
        {
            if (sc[i] == -1)
                target->decreaseStat(i, false);
            else
                target->decreaseStat(i, -sc[i]);
        }
        else if (sc[i] > 0)
        {
            if (sc[i] == -1)
                target->increaseStat(i, false);
            else
                target->increaseStat(i, sc[i]);
        }
    }
    
    return true;
}

void Pokemon::applyAttack(Pokemon* target, Move* move)
{
    Pokemon* attacker = this;
    Field* field = getTrainer()->getBattle()->getField();
    
    double typeBoost, pureDamage, sTAB, crit, modulus, other, attackMultiplier,
    specialDefMultiplier, modifier, spOrNot,
    damage, totalDamage, attack;
    
    int critThreshold;
    int phld1, phld2;
    
    if (target->hasVStatus(ProtectVStatus)
        || target->hasVStatus(ShieldVStatus))
    {
        target->protectDialogue();
        
        if (target->hasVStatus(ShieldVStatus))
        {
            if (move->getContact())
                attacker->decreaseStat(AttStat, 2);
        }
        
        return;
    }
    
    if (target->getAbility() == PLevitate && move->getType()
        == GroundType)
        // Target has Levitate and attacker is using GroundType move
    {
        typeBoost = 0.0;
        target->flashAbility();
    }
    else
        // Take type matchup into account
    {
        typeBoost = typeMultiplier(move->getType(), target->getType1(),
                                   target->getType2());
    }
    
    if (typeBoost == 0.0)
        // Target is immune to attack
    {
        cout << "It doesn't affect" << " "
        << target->getTrainer()->getTitleName() << "'s " << target->getName()
        << "." << endl;
        return;
    }
    
    pureDamage = move->getDamage();
    
    if (move->getType() == attacker->getType1() ||
        move->getType() == attacker->getType2())
        // Same Type Attack Bonus is 1.5x
    {
        sTAB = 1.5;
    }
    else
    {
        sTAB = 1.0;
    }
    
    critThreshold = 625;
    
    if (move->getEffect() == MHighCrit)
        critThreshold *= 2;
    
    if (randInt(0, 9999) < critThreshold)
        // Critical hits gain a 1.5x boost
        crit = 1.50;
    else
        crit = 1.00;
    
    // All attacks have an 85% mastery
    modulus = static_cast<double>(randInt(85, 100)) / 100.0;
    
    other = 1.0;
    
    if (move->getEffect() == MFoul)
    {
        if (target->getAbility() == PHugePower || target->getAbility()
            == PPurePower)
            attackMultiplier = 2.0;
        else
            attackMultiplier = 1.0;
        
        if (target->getStatus() == BurnStatus)
            attackMultiplier *= 0.5;
    }
    else
    {
        if (attacker->getAbility() == PHugePower || attacker->getAbility()
            == PPurePower)
            // Huge/Pure power ability: attack 2.0x
            attackMultiplier = 2.0;
        else
            attackMultiplier = 1.0;
        
        if (attacker->getStatus() == BurnStatus)
            // Attacker is burned: attack 0.5x
            attackMultiplier *= 0.5;
    }
    
    specialDefMultiplier = 1.0;
    
    if (field->getWeather() == Rain)
        // Water attacks get a 1.5x damage boost in Rain
    {
        if (move->getType() == WaterType)
            other = 1.5;
        else if (move->getType() == FireType)
            other = 0.5;
    }
    else if (field->getWeather() == Sunny)
        // Fire attacks get a 1.5x damage boost in Sun
    {
        if (move->getType() == FireType)
            other = 1.5;
        else if (move->getType() == WaterType)
            other = 0.5;
    }
    else if (field->getWeather() == Sandstorm)
        // Rock types get a SpD boost 1.5x in Sandstorm
    {
        specialDefMultiplier *= (target->getType1() == RockType
                                 || target->getType2() == RockType) ? 1.5
        : 1.0;
    }
    else if (field->getWeather() == Hail)
    {
        
    }
    
    if (attacker->getItem()->getID() == HLightBall && attacker->getID() == 25)
        // Pikachu holding a Light Ball
    {
        other *= 2.0;
    }
    
    modifier = typeBoost * sTAB * crit * modulus * other;
    
    // Physical attack
    if (move->getMoveType() == Physical)
    {
        // Foul Play: use target's Att stat
        if (move->getEffect() == MFoul)
            attack = static_cast<double>(target->getStats(AttStat) *
                                         attackMultiplier);
        else
            attack = static_cast<double>(attacker->getStats(AttStat) *
                                         attackMultiplier);
        
        spOrNot = attack / static_cast<double>(target->getStats(DefStat));
    }
    // Special attack
    else
    {
        spOrNot = static_cast<double>(attacker->getStats(SpAStat)) /
        (static_cast<double>(target->getStats(SpDStat)
                             * specialDefMultiplier));
    }
    
    damage = (((2.0 * attacker->getLevel() + 10.0) / 250.0) *
              (spOrNot) * pureDamage + 2.0);
    
    totalDamage = damage * modifier;
    
    if (move->getEffect() == MOHKO)
        totalDamage = target->getStats(HPStat);
    else if (move->getEffect() == MDamage20)
        totalDamage = 20;
    else if (move->getEffect() == MDamage40)
        totalDamage = 40;
    else if (move->getEffect() == MDamageLevel)
        totalDamage = attacker->getLevel();
    
    phld1 = target->getStatsStatus(HPStat);
    target->lowerHP(totalDamage);
    phld2 = phld1 - target->getStatsStatus(HPStat);
    
    if (crit == 1.50)
        cout << "A critical hit!" << endl;
    
    if (typeBoost > 1.0)
        cout << "It's super effective!" << endl;
    else if (typeBoost < 1.0)
        cout << "It's not very effective..." << endl;
    
    if (move->getEffect() == MOHKO)
        // OHKO move that hit (since it made it here)
        cout << "It's a one-hit KO!" << endl;
    
    applyEffect(target, move, phld2);
}

void Pokemon::applyEffect(Pokemon* target, Move* move, int drain)
{
    Pokemon* attacker = this;
    MoveEffect effect = move->getEffect();
    
    // Attacker side-effects (successful move execution)
    
    if (effect == MRampage && move->isThrash()
        && attacker->getRampageTurns() == 0)
        // Thrash-style rampage
    {
        attacker->addVStatus(RampageVStatus);
        attacker->setRampageTurns(randInt(2, 3));
    }
    
    if (effect == MOverheat)
        // Overheat effect
    {
        attacker->decreaseStat(SpAStat, 2);
    }
    
    if (effect == MFocusPunch)
        // Focus punch
        attacker->removeVStatus(FocusVStatus);
    
    // Drain
    if (effect == MDrain50 || effect == MDrain75)
    {
        cout << target->getName() << " had its energy drained!" << endl;
        
        switch (effect)
        {
            case MDrain50:
                increaseHP(drain * 0.5);
                break;
            default: // MDrain75
                increaseHP(drain * 0.75);
                break;
        }
    }
    
    // Target side-effects (successfully hit)
    
    if (target->isFainted() || target->getStats(HPStat) == 0)
        // did the target faint?
        // fainted pokemon don't get side-effects
        return;
    
    if ((effect == MFreeze10 || effect == MFreeze50) &&
        target->getType1() != IceType && target->getType2() != IceType &&
        target->getStatus() == HealthyStatus)
        // Freeze chance
    {
        int freezeChance;
        if (effect == MFreeze50)
            freezeChance = 50;
        else
            freezeChance = 10;
        
        if (randInt(0, 99) < freezeChance)
            target->setStatus(FreezeStatus);
    }
    
    if (effect == MFlinch10 || effect == MFlinch100 || effect == MFlinch20
        || effect == MFlinch30)
    {
        int flinchChance;
        
        switch (effect)
        {
            default:
                flinchChance = 30;
                break;
            case MFlinch10:
                flinchChance = 10;
                break;
            case MFlinch20:
                flinchChance = 20;
                break;
            case MFlinch100:
                flinchChance = 100;
                break;
        }
        
        if (getAbility() == PSereneGrace)
            flinchChance *= 2;
        
        if (randInt(0, 99) < flinchChance)
            target->addVStatus(FlinchVStatus);
    }
    
    if (effect == MBurn10 || effect == MBurn15 || effect == MBurn30)
        // Burn chance
    {
        if (target->getStatus() == HealthyStatus)
        {
            int chance;
            
            switch (effect)
            {
                default:
                    chance = 10; break;
                case MBurn15:
                    chance = 15; break;
                case MBurn30:
                    chance = 30; break;
            }
            
            if (randInt(0, 99) < chance)
                target->setStatus(BurnStatus);
        }
    }
    
    if (effect == MPoison10 || effect == MPoison15 || effect == MPoison30
        || effect == MPoison40)
        // Poison chance
    {
        if (target->getStatus() == HealthyStatus)
        {
            int chance;
            
            switch (effect)
            {
                default:
                    chance = 10; break;
                case MPoison15:
                    chance = 15; break;
                case MPoison30:
                    chance = 30; break;
                case MPoison40:
                    chance = 40; break;
            }
            
            if (randInt(0, 99) < chance)
                target->setStatus(PoisonStatus);
        }
    }
    
    if (effect == MTri20)
        // Tri attack
    {
        if (target->getStatus() == HealthyStatus)
        {
            if (randInt(0, 99) < 20)
            {
                switch(randInt(0, 2))
                {
                    default:
                        target->setStatus(BurnStatus);
                        break;
                    case 1:
                        target->setStatus(ParalyzeStatus);
                        break;
                    case 2:
                        target->setStatus(FreezeStatus);
                        break;
                }
            }
        }
    }
    
    if (effect == MParalyze10 || effect == MParalyze15 || effect == MParalyze30
        || effect == MParalyze100)
        // Paralyze chance
    {
        if (target->getStatus() == HealthyStatus)
        {
            int chance;
            
            switch (effect)
            {
                default:
                    chance = 10; break;
                case MParalyze15:
                    chance = 15; break;
                case MParalyze30:
                    chance = 30; break;
                case MParalyze100:
                    chance = 100; break;
            }
            
            if (randInt(0, 99) < chance)
                target->setStatus(ParalyzeStatus);
        }
    }
    
    if (target->hasVStatus(FocusVStatus))
        // Target flinched
    {
        target->removeVStatus(FocusVStatus);
        target->addVStatus(FFlinchVStatus);
    }
    
    if (effect == MLowerAcc100)
        // Lower accuracy
    {
        target->decreaseStat(AccStat, false);
    }
}

void Pokemon::applySideEffects(Move* move)
{
    // Attacker side effects not dependent on contact
    
    if (move->getEffect() == MSelfdestruct)
        // Self Destruct or Explosion
    {
        lowerHP(getStats(HPStat));
    }
}

const stack<Move*>* Pokemon::getMoveHistory() const
{
    return &m_moveHistory;
}

int Pokemon::getTurnsOut() const
{
    return m_turnsOut;
}

bool Pokemon::lockMove(Move* m)
{
    if (m_locked == NULL)
    {
        m_locked = m;
        return true;
    }
    else
        return false;
}

bool Pokemon::unlockMove()
{
    if (m_locked == NULL)
        return false;
    else
    {
        m_locked = NULL;
        return true;
    }
}

Move* Pokemon::getLockedMove() const
{
    return m_locked;
}

void Pokemon::removeStatus()
{
    m_status = HealthyStatus;
}

void Pokemon::removeVStatuses()
{
    m_vstatuses.clear();
}

void Pokemon::decTauntTurns()
{
    if (--m_tauntTurns == 0)
    {
        cout << getName() << "'s taunt wore off!" << endl;
        removeVStatus(TauntVStatus);
    }
    
    if (m_tauntTurns < 0)
        m_tauntTurns = 0;
}