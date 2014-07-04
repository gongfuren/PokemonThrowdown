//
//  Battle.cpp
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Battle.h"
#include "BattleData.h"
#include "Trainer.h"
#include "TrainerData.h"
#include "constants.h"
#include "strings.h"
#include "PokeData.h"
#include "MoveData.h"
#include "Side.h"
#include "Slot.h"
#include "Item.h"
#include "Player.h"
#include "Computer.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

// Battle Implementation

// Battle construction

Battle::Battle()
{
    m_field = new Field(this);
    
    // Zero out variables for now
    m_player = NULL;
    m_player2 = NULL;
    m_opponent = NULL;
    m_opponent2 = NULL;
    m_turns = 0;
    m_actor = NULL;
    m_initStage = 0;
    for (int i = 0; i < MAXPLAYERS; i++)
        m_participants[i] = NULL;
    
    // Custom Initialization
    for (int i = 0; i < 2; i++)
        customInit();
    
    chooseLead();
}

Battle::~Battle()
{
    for (int i = 0; i < NUMPLAYERS; i++)
        delete m_participants[i];
    
    delete m_field;
}

void Battle::chooseLead()
{
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        int choice;
        
        m_actor = m_participants[i];
        
        if (m_actor == m_player)
        {
            do
            {
                cout << bFStrings[15] << ":" << endl;
                
                for (int i = 0; i < 6; i++)
                    cout << i+1 << ": " << m_player->getPokemon(i)->getName()
                    << endl;
                
                cin >> choice;
            }
            while (choice <= 0 || choice > 6);
            
            choice -= 1;
        }
        else
        {
            choice = randInt(0, MAXPOKEMON-1);
        }
        
        m_actor->setCurrent(choice);
    }
}

void Battle::customInit()
{
    TrainerData protoman;
    
    int choice[4] = { -1, -1, -1, -1 };
    int pokemonID;
    
    do
    {
        cout << bFStrings[16] << " ";
        if (m_initStage == 0)
            cout << bFStrings[17];
        else
            cout << bFStrings[18];
        cout << "." << endl;
        
        for (int i = 0; i < NUMTRAINERS; i++)
            cout << i+1 << ": " << trainerlib[i].title << " "
            << trainerlib[i].name << endl;
        
        cin >> choice[0];
        if (choice[0] <= 0 || choice[0] > NUMTRAINERS)
            continue;
        
        protoman = trainerlib[choice[0]-1];
        
        do
        {
            cout << bFStrings[19] << " " << trainerlib[choice[0]-1].title
            << " " << trainerlib[choice[0]-1].name << "." << endl;
            
            cout << "1: " << bFStrings[20] << endl
                 << "2: " << bFStrings[21] << endl
                 << "3: " << "(" << bFStrings[22] << ")" << endl;
            
            cin >> choice[1];
            if (choice[1] <= 0 || choice[1] > 3)
                continue;
            
            if (choice[1] == 3)
            {
                choice[0] = -1;
                break;
            }
            
            if (choice[1] == 1)
                break;
            
            do
            {
                for (int i = 0; i < 6; i++)
                {
                    pokemonID = protoman.pokemonIDs[i];
                    cout << i+1 << ": " << pokelib[pokemonID].name
                    << endl;
                }
                cout << "7: " << "(" << bFStrings[22] << ")" << endl;
                
                cin >> choice[2];
                if (choice[2] <= 0 || choice[2] > 7)
                    continue;
                
                if (choice[2] == 7)
                {
                    choice[1] = -1;
                    break;
                }
                
                do
                {
                    pokemonID = protoman.pokemonIDs[choice[2]-1];
                    
                    cout << bFStrings[19] << " "
                    << pokelib[pokemonID].name << "."
                    << endl;
                    cout << "1: " << bFStrings[23] << endl
                         << "2: " << bFStrings[24] << endl
                         << "3: " << "(" << bFStrings[22] << ")" << endl;
                    
                    cin >> choice[3];
                    if (choice[3] <= 0 || choice[3] > 3)
                        continue;
                    
                    if (choice[3] == 3)
                    {
                        choice[2] = -1;
                        break;
                    }
                    
                    switch (choice[3])
                    {
                        default:
                            dispPokeSummary(pokelib[pokemonID]);
                            break;
                        case 2:
                            dispPokeMoves(pokelib[pokemonID]);
                            break;
                    }
                    
                    choice[3] = -1;
                }
                while (choice[3] <= 0 || choice[3] > 3);
            }
            while (choice[2] <= 0 || choice[2] > 7);
        }
        while (choice[1] <= 0 || choice[1] > 3);
    }
    while (choice[0] <= 0 || choice[0] > NUMTRAINERS);
    
    // Craft Trainer
    if (m_initStage == 0)
    {
        m_player = new Player(protoman, this);
        m_participants[m_initStage] = m_player;
        m_field->getSide(0)->addTrainer(m_player);
        m_initStage++;
    }
    else // m_initStage == 1
    {
        m_opponent = new Computer(protoman, this);
        m_participants[m_initStage] = m_opponent;
        m_field->getSide(1)->addTrainer(m_opponent);
    }
}

// Battle Flow

void Battle::start()
{
    greet();
    
    cycle();
}

void Battle::greet() const
{
    cout << m_opponent->getTitle() << " " << m_opponent->getName()
    << " " << bFStrings[34] << endl;
}

void Battle::clockTick()
{
    m_turns++;
    
    for (int i = 0; i < NUMPLAYERS; i++)
        m_participants[i]->getPokemon()->tick();
}

void Battle::cycle()
{
    for (;; clockTick())
    {
        // Summon pokemon (beginning of battle) or replace
        // fainted pokemon
        summonsPhase();
        
        // Action phase
        actionPhase();
        
        // Pre-battle phase (i.e. withdrawing)
        preBattlePhase();
        
        // Battle phase
        battlePhase();
        
        // Post-battle phase
        postBattlePhase();
        
        // Check if battle is over
        if (battleIsOver())
            break;
    }
}

void Battle::summonsPhase()
{
    for (int i = NUMPLAYERS-1; i >= 0; i--)
    {
        m_actor = m_participants[i];
        
        if (m_turns == 0)
            // First turn
        {
            m_actor->summonPokemon(0);
            m_field->getSide(i)->getSlot()->fillSlot(m_actor->getPokemon());
        }
        
        if (m_actor->getPokemon() == NULL || m_actor->getPokemon()->isFainted())
            // Choose replacement for fainted Pokemon
        {
            m_actor->replacePokemon();
        }
    }
    
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = m_participants[i];
        
        if (m_actor->getIntendedMove() == SWITCH)
        {
            // Replace fainted Pokemon
            m_actor->switchPokemon(false);
            m_field->getSide(i)->getSlot()->fillSlot(m_actor->getPokemon());
            
            m_actor->setIntendedMove(NODECIS);
        }
    }
    
    // Field event (i.e. weather)
    fieldEvent();
    
    // Event at summon (i.e. Intimidate, spikes)
    summonEffects();
    
    cout << endl;
}

void Battle::actionPhase()
{
    // Display battle status
    displayState(true);
    
    // Select actions
    actionSelect();
}

void Battle::preBattlePhase()
{
    if (m_player->getIntendedMove() == RUN)
        // Forfeit
        return;
    
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = m_participants[i];
        
        if (m_actor->getIntendedMove() == SWITCH)
        {
            m_actor->switchPokemon(true);
            
            m_field->getSide(i)->getSlot()->fillSlot(m_actor->getPokemon());
        }
    }
    
    summonEffects();
    
    // Event before battle phase (i.e. item)
    
}

void Battle::battlePhase()
{
    if (m_player->getIntendedMove() == RUN)
        // Forfeit
        return;
    
    int mID, tCtr, rCtr;
    Pokemon* pokemon = m_player->getPokemon();
    int priorityScore[NUMPLAYERS];
    Trainer* priorityArray[NUMPLAYERS];
    Trainer* tpa[NUMPLAYERS];
    Move* move;
    
    tCtr = 0;
    rCtr = 0;
    
    // Determine priorities
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = m_participants[i];
        pokemon = m_actor->getPokemon();
        mID = pokemon->getIntendedMove();
        move = pokemon->getMove(mID);
        
        priorityScore[i] = move->detPriorityScore();
    }
    
    for (int p = MAXPRIORITY; p >= MINPRIORITY; p--)
    {
        rCtr = 0;
        
        for (int i = 0; i < NUMPLAYERS; i++)
        {
            if (priorityScore[i] == p)
                tpa[rCtr++] = m_participants[i];
        }
        
        sortSpeeds(tpa, rCtr);
        
        for (int i = 0; i < rCtr; i++)
        {
            priorityArray[tCtr++] = tpa[i];
        }
    }
    
    // Event before moves are executed (i.e. Mega Evolution)
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = m_participants[i];
        pokemon = m_actor->getPokemon();
        
        if (m_actor->getIntendedMove() == MEGA)
        {
            pokemon->megaEvolve();
        }
    }
    
    summonEffects();
    
    // Do actions for certain moves (i.e. Focus Punch, Bide)
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = m_participants[i];
        int actorMove = m_actor->getIntendedMove();
        pokemon = m_actor->getPokemon();
        int moveID = pokemon->getIntendedMove();
        move = pokemon->getMove(moveID);
        
        if ((actorMove == FIGHT || actorMove == MEGA)
            && move->getEffect() == MFocusPunch)
        {
            cout << pokemon->getName() << " " << bFStrings[35] << endl;
            pokemon->addVStatus(FocusVStatus);
        }
    }
    
    // Cycle through pokemon with highest priority first
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = priorityArray[i];
        int actorMove = m_actor->getIntendedMove();
        pokemon = m_actor->getPokemon();
        int moveID = pokemon->getIntendedMove();
        move = pokemon->getMove(moveID);
        Pokemon* target;
        
        if (pokemon->isFainted())
            // a Pokemon was KO'd
            continue;
        
        if (actorMove == SWITCH || actorMove == BAG)
            // don't attack
            continue;
        
        int j;
        if (i == 0)
            j = 1;
        else
            j = 0;
        
        switch (move->getTarget())
        {
            case Self:
                target = pokemon;
                break;
                // Temporary targeting solution (TODO)
            default:
                target = priorityArray[j]->getPokemon();
                break;
        }
        
        if (pokemon->passThroughStatus() && pokemon->executeMove(target))
            ;
        else
        {
            displayState(false);
            pokemon->recordMove(false);
        }
        
        //
        if (pokemon->hasVStatus(RampageVStatus) && move->isThrash())
            // Pokemon is on a rampage
        {
            int rt = pokemon->getRampageTurns()-1;
            pokemon->setRampageTurns(rt);
            if (rt == 0)
            {
                pokemon->removeVStatus(RampageVStatus);
                
                cout << m_player->getTitle() << " " <<
                m_player->getName() << "'s " <<
                pokemon->getName() << " " << bFStrings[36] << endl;
                
                pokemon->addVStatus(ConfuseVStatus);
            }
        }
    }
}

void Battle::postBattlePhase()
{
    if (m_player->getIntendedMove() == RUN || m_player->getVictory()
        || m_opponent->getVictory() || checkWin())
        // Forfeit || battle has been won
        return;
    
    m_field->weatherContinue();
    checkFaint();
    
    // TODO: implement item effects here and at other item-use points
    
    for (int i = 0; i < NUMPLAYERS; i++)
        statusEffect(m_participants[i]);
    
    checkFaint();
    
    // Reset moves
    for (int i = 0; i < NUMPLAYERS; i++)
        m_participants[i]->setIntendedMove(NODECIS);
}

bool Battle::battleIsOver() const
{
    if (m_player->getVictory() || m_opponent->getVictory() || checkWin())
    {
        end();
        return true;
    }
    else
    {
        return false;
    }
}

void Battle::sortSpeeds(Trainer* trainers[], int number)
{
    for (int i = 0; i < number; i++)
    {
        for (int j = i+1; j < number; j++)
        {
            if (speedCompare(trainers[j]->getPokemon(),
                             trainers[i]->getPokemon()) > 0)
            {
                swap(&trainers[j], &trainers[i]);
            }
        }
    }
}

void Battle::swap(Trainer** trainerA, Trainer** trainerB)
{
    Trainer* temp = *trainerA;
    *trainerA = *trainerB;
    *trainerB = temp;
}

int Battle::speedCompare(const Pokemon* pokemonA, const Pokemon* pokemonB)
const
{
    double smA = 1.0, smB = 1.0;
    int efSA, efSB;
    
    // Take paralysis into account
    if (pokemonA->getStatus() == ParalyzeStatus)
        smA = 0.25;
    if (pokemonB->getStatus() == ParalyzeStatus)
        smB = 0.25;

    efSA = pokemonA->getStats(SPESTAT) * smA;
    efSB = pokemonB->getStats(SPESTAT) * smB;
    
    if (efSA > efSB)
    {
        return 1;
    }
    else if (efSB > efSA)
    {
        return -1;
    }
    else
    {
        int ft = (static_cast<bool>(randInt(0,1))) ? 1 : -1;
        return ft;
    }
}

void Battle::actionSelect()
{    
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_participants[i]->actionSelect();
    }
}

void Battle::fieldEvent()
{
    if (m_turns == 0)
        // Weather event
        m_field->initializeWeather();
}

void Battle::summonEffects()
{
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        // Ability cast point
        m_participants[i]->getPokemon()->castAbility();
    }
}

void Battle::turnCount() const
{
    ostringstream o;
    
    if (m_field->getWeather() != NoWeather)
        o << " (" << weatherStrings[m_field->getWeather()] << ")";
    
    cout << bFStrings[37] << " " << m_turns+1 << o.str() << endl;
}

void Battle::statusEffect(Trainer* trainer) const
{
    Pokemon* pokemon = trainer->getPokemon();
    
    pokemon->removeShortStatus();
    
    if (pokemon->isFainted())
        return;
    
    if (pokemon->getStatus() == BurnStatus)
    {
        cout << trainer->getTitle() << " " << trainer->getName()
        << "'s " << pokemon->getName() << " " << bFStrings[38] << endl;
        pokemon->lowerHP(static_cast<double>(pokemon->getBStats(HPSTAT))
                         * (0.125));
    }
    else if (pokemon->getStatus() == PoisonStatus)
    {
        cout << trainer->getTitle() << " " << trainer->getName() << "'s "
        << pokemon->getName() << " " << bFStrings[39] << endl;
        pokemon->lowerHP(static_cast<double>(pokemon->getBStats(HPSTAT))
                         * (0.125));
    }
    else if (pokemon->getStatus() == ToxicStatus)
    {
        pokemon->setToxicTurns(pokemon->getToxicTurns()+1);
        cout << trainer->getTitle() << " " << trainer->getName() << "'s "
        << pokemon->getName() << " " << bFStrings[39] << endl;
        pokemon->lowerHP(static_cast<double>(pokemon->getBStats(HPSTAT)) *
                           (pokemon->getToxicTurns() * (0.0625)));
    }
}

Weather Battle::getWeather() const
{
    return getField()->getWeather();
}

string Battle::statusText(Pokemon* pokemon, bool showStats) const
{
    ostringstream o;
    
    o << statusStrings[pokemon->getStatus()];
    
    if (showStats)
    {
        for (int i = ConfuseVStatus; i <= FFlinchVStatus; i++)
        {
            VolatileStatus vs = static_cast<VolatileStatus>(i);
            if (pokemon->hasVStatus(vs))
                o << ' ' << vstatusStrings[vs];
        }
        
        for (int i = ATTSTAT; i < NUMALLSTATS; i++)
        {
            if (pokemon->getStatsStatus(i) != 0)
            {
                int statstatus = pokemon->getStatsStatus(i);
                
                o << ' ';
                o << statStrings[i];
                
                if (statstatus > 0)
                    o << '+';
                
                o << statstatus;
            }
        }
    }
    
    return o.str();
}

void Battle::displayState(bool showTurnCount) const
{
    if (showTurnCount)
        turnCount();
    
    for (int i = NUMPLAYERS-1; i >= 0; i--)
        m_participants[i]->displayState();
}

void Battle::applyStatus(Trainer* trainerA, Trainer* trainerB, int whichMove)
{
    Pokemon* pokemon = trainerA->getPokemon();
    Pokemon* target = trainerB->getPokemon();
    Move* move = trainerA->getPokemonMove(whichMove);
    MoveEffect me = trainerA->getPokemonMove(whichMove)->getEffect();
    int healAmount = 0;
    
    int sc[NUMALLSTATS] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    
    if (me == MHeal50)
        // Calculate heal amount for Healing moves
    {
        healAmount = pokemon->getBStats(HPSTAT) / 2;
        
        if (move->getID() >= 234 && move->getID() <= 236)
        {
            // Weather-influenced healing move
            if (m_field->getWeather() == Sunny)
                healAmount = (2 * pokemon->getBStats(HPSTAT)) / 3;
            else if (m_field->getWeather() != NoWeather)
                healAmount = pokemon->getBStats(HPSTAT) / 4;
        }
    }
    else if (me == MHeal100)
        // Heal amount and sleep effect for Rest
    {
        healAmount = pokemon->getBStats(HPSTAT);
        
        cout << trainerB->getTitle() << " " << trainerB->getName() << "'s "
        << target->getName() << " " << bFStrings[40] << endl;
        
        pokemon->setStatus(SleepStatus, true);
    }
    
    switch (me)
    {
        case MHeal50:
        case MHeal100:
            cout << trainerB->getTitle() << " " << trainerB->getName() << "'s "
            << target->getName();
            if (target->increaseHP(healAmount))
                cout << "'s "<< bFStrings[41];
            else
                cout << "'s " << bFStrings[42];
            cout << endl;
            break;
        case MLowerAtt:
            sc[ATTSTAT] = -1;
            break;
        case MLowerAtt2:
            sc[ATTSTAT] = -2;
            break;
        case MUpAtt:
            sc[ATTSTAT] = 1;
            break;
        case MUpAtt2:
            sc[ATTSTAT] = 2;
            break;
        case MLowerDef:
            sc[DEFSTAT] = -1;
            break;
        case MLowerDef2:
            sc[DEFSTAT] = -2;
            break;
        case MUpDef:
            sc[DEFSTAT] = 1;
            break;
        case MUpDef2:
            sc[DEFSTAT] = 2;
            break;
        case MLowerSpA:
            sc[SPASTAT] = -1;
            break;
        case MLowerSpA2:
            sc[SPASTAT] = -2;
            break;
        case MUpSpA:
            sc[SPASTAT] = 1;
            break;
        case MUpSpA2:
            sc[SPASTAT] = 2;
            break;
        case MLowerSpD:
            sc[SPDSTAT] = -1;
            break;
        case MLowerSpD2:
            sc[SPDSTAT] = -2;
            break;
        case MUpSpD:
            sc[SPDSTAT] = 1;
            break;
        case MUpSpD2:
            sc[SPDSTAT] = 2;
            break;
        case MLowerSpe:
            sc[SPESTAT] = -1;
            break;
        case MLowerSpe2:
            sc[SPESTAT] = -2;
            break;
        case MUpSpe:
            sc[SPESTAT] = 1;
            break;
        case MUpSpe2:
            sc[SPESTAT] = 2;
            break;
        case MUpSpASpD:
            sc[SPASTAT] = 1;
            sc[SPDSTAT] = 1;
            break;
        case MUpAttDef:
            sc[ATTSTAT] = 1;
            sc[DEFSTAT] = 1;
            break;
        case MUpAttSpA:
            sc[ATTSTAT] = 1;
            sc[SPASTAT] = 1;
            break;
        case MUpDefSpD:
            sc[DEFSTAT] = 1;
            sc[SPDSTAT] = 1;
            break;
        case MUpAttSpe:
            sc[ATTSTAT] = 1;
            sc[SPESTAT] = 1;
            break;
        case MUpSpASpDSpe:
            sc[SPASTAT] = 1;
            sc[SPDSTAT] = 1;
            sc[SPESTAT] = 1;
            break;
        case MUpAll:
            for (int i = ATTSTAT; i < NUMSTATS; i++)
                sc[i] = 1;
            break;
        case MSun:
            if (m_field->getWeather() != Sunny)
                m_field->initializeWeather(Sunny);
            break;
        case MRain:
            if (m_field->getWeather() != Rain)
                m_field->initializeWeather(Rain);
            break;
        case MSandstorm:
            if (m_field->getWeather() != Sandstorm)
                m_field->initializeWeather(Sandstorm);
            break;
        case MHail:
            if (m_field->getWeather() != Hail)
                m_field->initializeWeather(Hail);
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
            target->setStatus(BurnStatus);
            break;
        case MSleep:
            target->setStatus(SleepStatus);
            break;
        case MPoison:
            target->setStatus(PoisonStatus);
            break;
        case MToxic:
            target->setStatus(ToxicStatus);
            break;
        case MParalyze:
            target->setStatus(ParalyzeStatus);
            break;
        default:
            break;
    }
    
    for (int i = ATTSTAT; i < NUMALLSTATS; i++)
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
}

void Battle::applyAttack(Trainer* trainerA, Trainer* trainerB,
                         int whichMove) const
{
    Pokemon* attacker = trainerA->getPokemon();
    Pokemon* target = trainerB->getPokemon();
    Move* attackMove = attacker->getMove(whichMove);

    double typeBoost, pureDamage, sTAB, crit, modulus, other, attackMultiplier,
    specialDefMultiplier, modifier, spOrNot,
    damage, totalDamage;
    
    int critThreshold;
    
    if (target->hasVStatus(ProtectVStatus)
        || target->hasVStatus(ShieldVStatus))
    {
        target->protectDialogue();
        
        if (target->hasVStatus(ShieldVStatus))
        {
            if (attackMove->getContact())
                attacker->decreaseStat(ATTSTAT, 2);
        }
        
        return;
    }
    
    if (target->getAbility() == PLevitate && attackMove->getType()
        == GroundType)
        // Target has Levitate and attacker is using GroundType move
    {
        typeBoost = 0.0;
        target->flashAbility();
    }
    else
        // Take type matchup into account
    {
        typeBoost = typeMultiplier(attackMove->getType(), target->getType1(),
                                   target->getType2());
    }
    
    if (typeBoost == 0.0)
        // Target is immune to attack
    {
        cout << bFStrings[43] << " " << trainerB->getTitle() << ' '
        << trainerB->getName() << "'s " << target->getName()
        << "." << endl;
        return;
    }
    
    pureDamage = attackMove->getDamage();

    if (attackMove->getType() == attacker->getType1() ||
        attackMove->getType() == attacker->getType2())
        // Same Type Attack Bonus is 1.5x
    {
        sTAB = 1.5;
    }
    else
    {
        sTAB = 1.0;
    }
    
    critThreshold = 625;
    
    if (attackMove->getEffect() == MHighCrit)
        critThreshold *= 2;
    
    if (randInt(0, 9999) < critThreshold)
        // Critical hits gain a 1.5x boost
        crit = 1.50;
    else
        crit = 1.00;
    
    // All attacks have an 85% mastery
    modulus = static_cast<double>(randInt(85, 100)) / 100.0;
    
    other = 1.0;
    
    if (attacker->getAbility() == PHugePower || attacker->getAbility()
        == PPurePower)
        // Huge/Pure power ability: attack 2.0x
        attackMultiplier = 2.0;
    else
        attackMultiplier = 1.0;
    
    if (attacker->getStatus() == BurnStatus)
        // Attacker is burned: attack 0.5x
        attackMultiplier *= 0.5;
    
    specialDefMultiplier = 1.0;
    
    if (m_field->getWeather() == Rain)
        // Water attacks get a 1.5x damage boost in Rain
    {
        if (attackMove->getType() == WaterType)
            other = 1.5;
        else if (attackMove->getType() == FireType)
            other = 0.5;
    }
    else if (m_field->getWeather() == Sunny)
        // Fire attacks get a 1.5x damage boost in Sun
    {
        if (attackMove->getType() == FireType)
            other = 1.5;
        else if (attackMove->getType() == WaterType)
            other = 0.5;
    }
    else if (m_field->getWeather() == Sandstorm)
        // Rock types get a SpD boost 1.5x in Sandstorm
    {
        specialDefMultiplier *= (target->getType1() == RockType
                                 || target->getType2() == RockType) ? 1.5
        : 1.0;
    }
    else if (m_field->getWeather() == Hail)
    {
        
    }
    
    if (attacker->getItem()->getID() == HLightBall && attacker->getID() == 25)
        // Pikachu holding a Light Ball
    {
        other *= 2.0;
    }
    
    modifier = typeBoost * sTAB * crit * modulus * other;
    
    if (trainerA->getPokemonMove(whichMove)->getMoveType() == Physical)
        // Physical attack
    {
        spOrNot = static_cast<double>(attacker->getStats(ATTSTAT) *
                attackMultiplier)
                / static_cast<double>(target->getStats(DEFSTAT));
    }
    else
        // Special attack
    {
        spOrNot = static_cast<double>(attacker->getStats(SPASTAT)) /
        (static_cast<double>(target->getStats(SPDSTAT)
                             * specialDefMultiplier));
    }
    
    damage = (((2.0 * attacker->getLevel() + 10.0) / 250.0) *
              (spOrNot) * pureDamage + 2.0);
    
    totalDamage = damage * modifier;
    
    if (attackMove->getEffect() == MOHKO)
        totalDamage = target->getStats(HPSTAT);
    else if (attackMove->getEffect() == MDamage20)
        totalDamage = 20;
    else if (attackMove->getEffect() == MDamage40)
        totalDamage = 40;
    else if (attackMove->getEffect() == MDamageLevel)
        totalDamage = attacker->getLevel();
    
    target->lowerHP(totalDamage);
    
    if (crit == 1.50)
        cout << bFStrings[44] << endl;
    
    if (typeBoost > 1.0)
        cout << bFStrings[45] << endl;
    else if (typeBoost < 1.0)
        cout << bFStrings[46] << endl;
    
    if (attackMove->getEffect() == MOHKO)
        // OHKO move that hit (since it made it here)
        cout << bFStrings[47] << endl;
    
    applyEffect(trainerA, trainerB, whichMove);
}

void Battle::applyEffect(Trainer* trainerA, Trainer* trainerB,
                         int whichMove) const
{
    Pokemon* attacker = trainerA->getPokemon();
    Pokemon* target = trainerB->getPokemon();
    Move* attackMove = attacker->getMove(whichMove);
    MoveEffect effect = attackMove->getEffect();
    
    // Attacker side-effects (successful move execution)
    
    if (effect == MRampage && attackMove->isThrash()
        && attacker->getRampageTurns() == 0)
        // Thrash-style rampage
    {
        attacker->addVStatus(RampageVStatus);
        attacker->setRampageTurns(randInt(2, 3));
    }
    
    if (effect == MOverheat)
        // Overheat effect
    {
        attacker->decreaseStat(SPASTAT, 2);
    }
    
    if (effect == MFocusPunch)
        // Focus punch
        attacker->removeVStatus(FocusVStatus);
    
    // Target side-effects (successfully hit)
    
    if (target->isFainted() || target->getStats(HPSTAT) == 0)
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
        target->decreaseStat(ACCSTAT, false);
    }
}

void Battle::applySideEffects(Trainer* trainer, int whichMove)
{
    // Attacker side effects not dependent on contact
    
    Move* attackMove = trainer->getPokemonMove(whichMove);
    Pokemon* attacker = trainer->getPokemon();
    
    if (attackMove->getEffect() == MSelfdestruct)
        // Self Destruct or Explosion
    {
        attacker->lowerHP(attacker->getStats(HPSTAT));
    }

}

void Battle::checkFaint() const
{
    for (int i = 0; i < NUMPLAYERS; i++)
        m_participants[i]->checkFaint();
}

Trainer* Battle::getParticipants(int i) const
{
    return m_participants[i];
}

Trainer* Battle::getPlayer() const
{
    return m_player;
}

Trainer* Battle::getOpponent() const
{
    return m_opponent;
}

Field* Battle::getField() const
{
    return m_field;
}

bool Battle::checkWin() const
{
    bool playerWon = true;
    bool opponentWon = true;

    for (int i = 0; i < MAXPOKEMON; i++)
    {
        if (m_player->getPokemon(i) != NULL
            && !m_player->getPokemon(i)->isFainted())
            opponentWon = false;
        
        if (m_opponent->getPokemon(i) != NULL
            && !m_opponent->getPokemon(i)->isFainted())
            playerWon = false;
    }
    
    if (playerWon)
        m_player->setVictory();
    
    if (opponentWon)
        m_opponent->setVictory();
    
    return (playerWon || opponentWon);
}

void Battle::end() const
{
    if (m_player->getVictory() && m_opponent->getVictory())
    {
        cout << bFStrings[49] << endl;
    }
    else if (m_player->getVictory())
    {
        cout << m_player->getTitle() << " " << m_player->getName() << " "
        << bFStrings[50] << endl << bFStrings[51] << " $"
        << m_opponent->getReward() << " " << bFStrings[52] << endl;
    }
    else if (m_opponent->getVictory())
    {
        cout << m_opponent->getTitle() << " " << m_opponent->getName() << " "
        << bFStrings[50] << endl;
    }
}

void Battle::dispPokeSummary(int slotNumber) const
{
    ostringstream pout;
    Pokemon* pokemon = m_player->getPokemon(slotNumber);
    
    // Name
    pout << pokemon->getName() << " "
    // Level
    << bFStrings[28] << " " << pokemon->getLevel() << " "
    // Gender
    << genderStrings[pokemon->getGender()] << " "
    // Status
    << statusText(pokemon, false) << endl

    // Type(s)
    << typeStrings[pokemon->getType1()];
    if (pokemon->getType2() != NoType)
        pout << "/" << typeStrings[pokemon->getType2()];
    pout << endl;
    
    // Item
    pout << bFStrings[25] << ": " << itemStrings[pokemon->getItem()->getID()]
    << endl
    
    // Ability
    << bFStrings[26] << ": " << abilityStrings[pokemon->getAbility()] << endl
    
    // Nature
    << bFStrings[48] << ": " << natureStrings[pokemon->getNature()] << endl
    
    // Stats
    << statFullStrings[HPSTAT] << ": " << pokemon->getStats(HPSTAT) << '/'
    << pokemon->getBStats(HPSTAT) << endl;
    for (int i = ATTSTAT; i < NUMSTATS; i++)
        pout << statFullStrings[i] << ": " << pokemon->getBStats(i) << endl;
    
    // Description
    if (pokemon->getDescription() != "")
        pout << pokemon->getDescription();
    pout << endl;
    
    cout << pout.str();
}

void Battle::dispPokeSummary(const PokeData pokemon) const
{
    // Name
    cout << pokemon.name << " "
    // Level
    << bFStrings[28] << " " << pokemon.level << endl;
    
    // Type
    cout << typeStrings[pokemon.type1];
    if (pokemon.type2 != NoType)
        cout << "/" << typeStrings[pokemon.type2];
    cout << endl;
    
    // Item
    cout << bFStrings[25] << ": " << itemStrings[pokemon.item] << endl;
    
    // Ability
    cout << bFStrings[26] << ": " << abilityStrings[pokemon.ability] << endl;
    
    // Stats
    cout << bFStrings[27] << ":" << endl;
    for (int i = 0; i < 6; i++)
        cout << statFullStrings[i] << ": " << pokemon.stats[i] << endl;
    
    // Description
    if (pokemon.description != "")
        cout << pokemon.description << endl;
}

void Battle::dispPokeMoves(int pokemon) const
{
    Move* move;
    
    for (int i = 0; i < MAXMOVES; i++)
    {
        move = m_player->getPokemon(pokemon)->getMove(i);
        
        ostringstream pout;
        
        string pOS;
        if (move->getMoveType() == Status)
        {
            pOS += bFStrings[33];
            pOS += ": ";
            pOS += moveTypeStrings[Status];
        }
        else
        {
            pOS += bFStrings[32];
            pOS += ": ";
            
            if (move->getMoveType() == Physical)
                pOS += moveTypeStrings[Physical];
            else
                pOS += moveTypeStrings[Special];
        }
        
        pout << move->getName() << endl << bFStrings[29] << ": "
        << typeStrings[move->getType()] << " " << bFStrings[30]
        << ": ";
        
        if (move->getDamage() == -1)
            pout << '-';
        else
            pout << move->getDamage();
        
        pout << " " << bFStrings[31] << ": ";
        
        if (move->getAccuracy() == -1)
            pout << '-';
        else
            pout << move->getAccuracy();
        
        pout << " " << pOS;
        
        if (move->getDescription() != "")
            pout << move->getDescription() << endl;
        
        cout << pout.str() << endl;
    }
}

void Battle::dispPokeMoves() const
{
    dispPokeMoves(0);
}

void Battle::dispPokeMoves(const PokeData pokemon) const
{
    ostringstream o;
    
    int moveID;
    
    for (int i = 0; i < 4; i++)
    {
        moveID = pokemon.moveIDs[i];
        MoveData m = movelib[moveID];
        o << m.name << endl
        
        << bFStrings[29] << ": " << typeStrings[m.type] << " "
        << bFStrings[30] << ": ";
        
        if (m.damage == -1)
            o << '-';
        else
            o << m.damage;
        
        o << " " << bFStrings[31] << ": ";
        
        if (m.accuracy == -1)
            o << '-';
        else
            o << m.accuracy;
        
        o << " ";
        
        if (m.moveType == Physical || m.moveType == Special)
            o << bFStrings[32] << ": ";
        else
            o << bFStrings[33] << ": ";
        
        o << moveTypeStrings[m.moveType] << endl;
        
        if (m.description != "")
            o << m.description << endl;
    }
    
    cout << o.str();
}
