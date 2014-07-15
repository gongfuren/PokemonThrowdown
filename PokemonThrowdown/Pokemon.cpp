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

Pokemon::Pokemon(int pokemonID, Trainer* trainer, int whichAbility)
: m_trainer(trainer)
{
    standardInit(pokelib[pokemonID], whichAbility);
}

Pokemon::Pokemon(pokedata h, Trainer* trainer, int whichAbility)
: m_trainer(trainer)
{
    standardInit(h, whichAbility);
}

Pokemon::~Pokemon()
{
    for (int i = 0; i < MAXMOVES; i++)
        delete m_moves[i];
}

void Pokemon::transformInit(int pokemonID)
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

void Pokemon::standardInit(pokedata h, int whichAbility)
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
    m_ability = h.ability[whichAbility];
    m_item = new Item(h.item);
    m_description = h.description;
    m_sleepTurns = 0;
    m_toxicTurns = 0;
    m_rampageTurns = 0;
    m_ID = h.ID;
    m_form = 0;
    m_turnsOut = -1;
    m_fainted = false;
    
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
        if (h.moveIDs[i] != -1)
            m_moves[i] = new Move(h.moveIDs[i], this);
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
        
        transformInit(m_item->getID() - HVenusaurite + 722);
        
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
            transformInit(762);
            
            cout <<  "Blade";
        }
        else
            // Blade to Shield
        {
            transformInit(681);
            
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
                // Poison and Steel types cannot be poisoned
                return;
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
    bool moveHits, changeForm;
    int moveAccuracy, whatForm;
    
    if (move == NULL)
    {
        move = getMove(intendedMove);
    }
    
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
    
    cout << getTrainer()->getTitleName() << "'s "
    << getName() << " " << "used" << " " << move->getName() << "!"
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
            battle->applyStatus(getTrainer(), getTrainer(), getMove(intendedMove));
        else
            // Attack
            battle->applyAttack(getTrainer(), getTrainer(), getMove(intendedMove));
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
            battle->applyStatus(getTrainer(), target->getTrainer(),
                                getMove(intendedMove));
        else
            // Attack
            battle->applyAttack(getTrainer(), target->getTrainer(),
                                getMove(intendedMove));
    }
    
    battle->applySideEffects(getTrainer(), getMove(intendedMove));
    
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