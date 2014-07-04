//
//  Pokemon.cpp
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Pokemon.h"
#include "PokeData.h"
#include "Trainer.h"
#include "Battle.h"
#include "constants.h"
#include "strings.h"
#include "Item.h"

#include <iostream>
#include <string>
using namespace std;

Pokemon::Pokemon(int pokemonID, Trainer* trainer)
: m_trainer(trainer)
{
    standardInit(pokemonID);
}

Pokemon::Pokemon(PokeData h, Trainer* trainer)
: m_trainer(trainer)
{
    standardInit(h.ID);
}

Pokemon::~Pokemon()
{
    for (int i = 0; i < MAXMOVES; i++)
        delete m_moves[i];
}

void Pokemon::transformInit(int pokemonID)
{
    PokeData me = pokelib[pokemonID];
    
    m_name = me.name;
    m_type1 = me.type1;
    m_type2 = me.type2;
    m_ability = me.ability;
    
    for (int i = ATTSTAT; i < NUMSTATS; i++)
    {
        int adder = 5;
        m_bStats[i] = ((2 * me.stats[i] + m_IVs[i] + m_EVs[i] / 4) * m_level
                       / 100 + adder) * natureMultiplier(m_nature, i-1);
    }
}

void Pokemon::standardInit(int pokemonID)
{
    m_name = pokelib[pokemonID].name;
    m_type1 = pokelib[pokemonID].type1;
    m_type2 = pokelib[pokemonID].type2;
    m_status = HealthyStatus;
    m_gender = pokelib[pokemonID].gender;
    m_intendedMove = 0;
    m_level = pokelib[pokemonID].level;
    m_nature = (pokelib[pokemonID].nature == NoNature)
    ? static_cast<Nature>(randInt(HARDY, NUMNATURES-1)) : pokelib[pokemonID].nature;
    m_ability = pokelib[pokemonID].ability;
    m_item = new Item(pokelib[pokemonID].item);
    m_description = pokelib[pokemonID].description;
    m_sleepTurns = 0;
    m_toxicTurns = 0;
    m_rampageTurns = 0;
    m_ID = pokemonID;
    m_form = 0;
    m_turnsOut = -1;
    m_fainted = false;
    
    for (int i = HPSTAT; i < NUMSTATS; i++)
    {
        int adder = (i == HPSTAT) ? 10 + m_level : 5;
        double nature = (i == HPSTAT) ? 1.0 : natureMultiplier(m_nature, i-1);
        m_IVs[i] = (pokelib[pokemonID].IVs[i] == -1) ? randInt(0, 31)
        : pokelib[pokemonID].IVs[i];
        m_EVs[i] = (pokelib[pokemonID].EVs[i] == -1) ? randInt(0, 85)
        : pokelib[pokemonID].EVs[i];
        m_bStats[i] = ((2 * pokelib[pokemonID].stats[i] + m_IVs[i] + m_EVs[i]
                        / 4) * m_level / 100 + adder) * nature;
    }
    
    m_statsStatus[HPSTAT] = m_bStats[HPSTAT];
    
    for (int i = ATTSTAT; i < NUMALLSTATS; i++)
    {
        m_statsStatus[i] = 0;
    }
    
    for (int i = 0; i < MAXMOVES; i++)
    {
        if (pokelib[pokemonID].moveIDs[i] != -1)
            m_moves[i] = new Move(pokelib[pokemonID].moveIDs[i], this);
        else
            m_moves[i] = new Move(randInt(0, MAXNUMMOVES-1), this);
    }
    
    if (m_gender == NoGender)
        m_gender = static_cast<Gender>(randInt(0, 1));
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
    
    for (int i = 722; i <= 749; i++)
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
    m_vstatuses.clear();
    
    // Undo volatile transformations
    if (m_ID == 681)
        // Aegislash
    {
        if (m_form == 1)
            transformInit(681);
    }
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
    if (whichStat == HPSTAT)
        return m_statsStatus[whichStat];
    else if (whichStat == ACCSTAT || whichStat == EVASTAT)
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
            opponent->decreaseStat(ATTSTAT, false);
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
            cout << getName() << " " << bFStrings[74] << endl;
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
    m_statsStatus[HPSTAT] = 0;
    
    m_fainted = true;
    setStatus(FaintStatus);
}

void Pokemon::lowerHP(int howMuch)
{
    m_statsStatus[HPSTAT] -= howMuch;
    
    if (m_statsStatus[HPSTAT] <= 0)
    {
        m_statsStatus[HPSTAT] = 0;
    }
}

bool Pokemon::hasMaxHP() const
{
    return (m_statsStatus[HPSTAT] == m_bStats[HPSTAT]);
}

bool Pokemon::increaseHP(int howMuch)
{
    if (hasMaxHP())
        return false;
    
    m_statsStatus[HPSTAT] += howMuch;
    
    if (m_statsStatus[HPSTAT] >= m_bStats[HPSTAT])
    {
        m_statsStatus[HPSTAT] = m_bStats[HPSTAT];
    }
    
    return true;
}

void Pokemon::protectDialogue() const
{
    Trainer* trainer = getTrainer();

    cout << trainer->getTitle() << " " << trainer->getName() << "'s "
    << m_name << " " << bFStrings[75] << endl;
}

void Pokemon::avoidDialogue() const
{
    Trainer* trainer = getTrainer();
    
    cout << trainer->getTitle() << " " << trainer->getName() << "'s "
    << getName() << " " << bFStrings[76] << endl;
}

bool Pokemon::decreaseStat(int whichStat, bool silent)
{
    bool normalExecution = true;
    
    if (!silent && m_ability == PClearBody)
        // Clear Body cancellation
    {
        normalExecution = false;
        
        flashAbility();
        
        cout << getTrainer()->getTitle() << " " << getTrainer()->getName()
        << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
        << bFStrings[77] << endl;
    }
    
    if (normalExecution)
    {
        if (!silent && m_statsStatus[whichStat] <= -6)
        {
            cout << getTrainer()->getTitle() << " " << getTrainer()->getName()
            << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
            << bFStrings[78] << endl;
        }
        else
        {
            if (!silent)
            {
                cout << getTrainer()->getTitle() << " "
                << getTrainer()->getName() << "'s " << m_name << "'s "
                << statFullStrings[whichStat] << " " << bFStrings[79] << endl;
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
        cout << getTrainer()->getTitle() << " " << getTrainer()->getName()
        << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
        << bFStrings[78] << endl;
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
                << statFullStrings[whichStat] << " " << bFStrings[80] << endl;
            else
            {
                switch (decrease)
                {
                    default:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << bFStrings[79]
                        << endl;
                        break;
                    case 1:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << bFStrings[81]
                        << endl;
                        break;
                    case 2:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << bFStrings[82]
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
            cout << getTrainer()->getTitle() << " " << getTrainer()->getName()
            << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
            << bFStrings[83] << endl;
        
        return true;
    }
    
    if (!silent)
        cout << getTrainer()->getTitle() << " " << getTrainer()->getName()
        << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
        << bFStrings[86] << endl;
    
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
        cout << getTrainer()->getTitle() << " " << getTrainer()->getName()
        << "'s " << m_name << "'s " << statFullStrings[whichStat] << " "
        << bFStrings[84] << endl;
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
                << bFStrings[85] << " " << statFullStrings[whichStat] << "!"
                << endl;
            else
            {
                switch (increase)
                {
                    default:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << bFStrings[86]
                        << endl;
                        break;
                    case 1:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << bFStrings[87]
                        << endl;
                        break;
                    case 2:
                        cout << getTrainer()->getTitle() << " "
                        << getTrainer()->getName() << "'s " << m_name << "'s "
                        << statFullStrings[whichStat] << " " << bFStrings[88]
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
        cout << getTrainer()->getTitle() << ' ' << getTrainer()->getName()
        << "'s ";
    
    if (m_status == ParalyzeStatus && thru < 25)
    {
        cout << m_name << " " << bFStrings[89] << endl;
        pass = false;
    }
    else if (m_status == SleepStatus)
    {
        if (m_sleepTurns-- > 0)
        {
            cout << m_name << " " << bFStrings[90] << endl;
            pass = false;
        }
        else
        {
            cout << m_name << " " << bFStrings[91] << endl;
            m_status = HealthyStatus;
            pass = true;
        }
    }
    else if (m_status == FreezeStatus)
    {
        if (thru < 80)
        {
            cout << m_name << " " << bFStrings[92] << endl;
            pass = false;
        }
        else
        {
            cout << m_name << " " << bFStrings[93] << endl;
            m_status = HealthyStatus;
            pass = true;
        }
    }
    else if (hasVStatus(FlinchVStatus))
    {
        cout << m_name << " " << bFStrings[94] << endl;
        pass = false;
    }
    else if (hasVStatus(FFlinchVStatus))
    {
        cout << m_name << " " << bFStrings[95] << endl;
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
            cout << m_name << " " << bFStrings[96] << endl;
            removeVStatus(ConfuseVStatus);
        }
        else
        {
            cout << m_name << " " << bFStrings[97] << endl;
            
            if (thru < 500)
            {
                cout << m_name << " " << bFStrings[98] << endl;
                
                int pureDamage = 40;
                int attackMultiplier = 1.0;
                if (getAbility() == PHugePower || getAbility() == PPurePower)
                    attackMultiplier = 2.0;
                int spOrNot
                = static_cast<double>(getStats(ATTSTAT) * attackMultiplier)
                / static_cast<double>(getStats(DEFSTAT));
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
        << bFStrings[99] << " " << getTrainer()->getName() << "'s "
        << bFStrings[100] << endl;
        
        cout << m_name << " " << bFStrings[101] << " " << m_name << "!"
        << endl;
        
        transformInit(m_item->getID() - HVenusaurite + 722);
        
        getTrainer()->setUsedMega();
    }
    else if (m_ID == 681)
        // Aegislash
    {
        flashAbility();
        
        cout << bFStrings[102] << " ";
        
        if (m_form == 0)
            // Shield to Blade
        {
            transformInit(762);
            
            cout << bFStrings[107];
        }
        else
            // Blade to Shield
        {
            transformInit(681);
            
            cout << bFStrings[108];
        }
        
        cout << " " << bFStrings[103] << endl;
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

void Pokemon::setStatus(PokeStatus status, bool rest)
{
    if (status != FaintStatus && getStatus() != HealthyStatus)
        return;
    
    switch (status)
    {
        case FaintStatus:
            break;
        case FreezeStatus:
            if ((getType1() == IceType || getType2() == IceType) ||
                getTrainer()->getBattle()->getWeather() == Sunny)
                // Ice types cannot be frozen
                // No freezing occurs in sunny weather
                return;
            break;
        case ParalyzeStatus:
            if (getType1() == ElectricType || getType2() == ElectricType)
                // Electric types cannot be paralyzed
                return;
            break;
        case BurnStatus:
            if (getType1() == FireType || getType2() == FireType)
                // Fire types cannot be burned
                return;
            break;
        case PoisonStatus:
        case ToxicStatus:
            if (getType1() == PoisonType || getType2() == PoisonType ||
                getType1() == SteelType || getType2() == SteelType)
                // Poison and steel types cannot be poisoned
                return;
            break;
        case SleepStatus:
            break;
        default:
            break;
    }
    
    m_status = status;
    
    if (!rest)
        cout << getTrainer()->getTitle() << ' ' << getTrainer()->getName()
        << "'s " << m_name << " " << statusStartStrings[status] << endl;
    
    if (status == SleepStatus)
    {
        if (!rest)
            m_sleepTurns = randInt(1, 3);
        else
            m_sleepTurns = 2;
    }
}

void Pokemon::setIntendedMove(int choice)
{
    m_intendedMove = choice;
}

void Pokemon::checkFaint()
{
    if (!isFainted() && getStats(HPSTAT) == 0)
        setFainted();
}

bool Pokemon::executeMove(Pokemon* target)
{
    int intendedMove = getIntendedMove();
    Move* move = getMove(intendedMove);
    Battle* battle = getTrainer()->getBattle();
    Weather weather;
    bool moveHits, changeForm;
    int moveAccuracy, whatForm;
    
    if (isFainted())
        return false;
    
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
    
    cout << getTrainer()->getTitle() << ' ' << getTrainer()->getName() << "'s "
    << getName() << " " << bFStrings[104] << " " << move->getName() << "!"
    << endl;
    
    moveAccuracy = move->getAccuracy();
    
    weather = battle->getWeather();
    
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
    else
        // Normal accuracy calculation
    {
        double a = getStats(ACCSTAT);
        double b = target->getStats(EVASTAT);
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
        cout << bFStrings[105] << endl;
        
        return false;
    }
    
    if (move->getTarget() == Self || move->getTarget() == None)
        // Move used on self or other
    {
        if (move->getMoveType() == Status)
            // Status move
            battle->applyStatus(getTrainer(), getTrainer(), intendedMove);
        else
            // Attack
            battle->applyAttack(getTrainer(), getTrainer(), intendedMove);
    }
    else
        // Targeting pokemon other than self
    {
        if (target == NULL || target->isFainted())
        {
            cout << bFStrings[106] << endl;
            
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
            battle->applyStatus(getTrainer(), target->getTrainer(),
                                intendedMove);
        else
            // Attack
            battle->applyAttack(getTrainer(), target->getTrainer(),
                                intendedMove);
    }
    
    battle->applySideEffects(getTrainer(), intendedMove);
    
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