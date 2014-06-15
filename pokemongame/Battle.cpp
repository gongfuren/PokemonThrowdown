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
#include "PokeData.h"
#include "MoveData.h"
#include "Side.h"
#include "Slot.h"
#include "Item.h"
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
    
    m_player = NULL;
    m_player2 = NULL;
    m_opponent = NULL;
    m_opponent2 = NULL;
    m_turns = 0;
    m_actor = NULL;
    for (int i = 0; i < MAXPLAYERS; i++)
        m_participants[i] = NULL;
    
    // Custom Initialization:
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
                cout << "Choose lead Pokemon:" << endl;
                
                for (int i = 0; i < 6; i++)
                    cout << i+1 << ": " << m_player->getPokemon(i)->getName() << endl;
                
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
    initStage = 0;
    customInit(m_player);
    initStage = 1;
    customInit(m_opponent);
}

void Battle::customInit(Trainer* trainerA)
{
    TrainerData protoman;
    
    int choice[4] = { -1, -1, -1, -1 };
    int pokemonID;
    
    do
    {
        cout << "Choose ";
        if (initStage == 0)
            cout << "a trainer";
        else
            cout << "an opponent";
        cout << "." << endl;
        
        for (int i = 0; i < NUMTRAINERS; i++)
        {
            cout << i+1 << ": " << trainerlib[i].title << " "
            << trainerlib[i].name << endl;
        }
        
        cin >> choice[0];
        if (choice[0] <= 0 || choice[0] > NUMTRAINERS)
            continue;
        
        protoman = trainerlib[choice[0]-1];
        
        do
        {
            cout << "You chose " << trainerlib[choice[0]-1].title << " "
            << trainerlib[choice[0]-1].name << "." << endl;
            
            cout << "1: Confirm" << endl
                 << "2: Pokemon" << endl
                 << "3: (Cancel)" << endl;
            
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
                cout << "7: (Cancel)" << endl;
                
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
                    
                    cout << "You chose "
                    << pokelib[pokemonID].name << "."
                    << endl;
                    cout << "1: Summary" << endl
                         << "2: Check Moves" << endl
                         << "3: (Cancel)" << endl;
                    
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
                            pokeSummary(pokelib[pokemonID]);
                            break;
                        case 2:
                            pokeMoveInfo(pokelib[pokemonID]);
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
    if (initStage == 0)
    {
        m_player = new Trainer(protoman, this, false);
        m_participants[initStage] = m_player;
        m_field->getSide(0)->addTrainer(m_player);
    }
    else // initStage == 1
    {
        m_opponent = new Trainer(protoman, this);
        m_participants[initStage] = m_opponent;
        m_field->getSide(1)->addTrainer(m_opponent);
    }
}

void Battle::pokeSummary(const PokeData pokemon) const
{
    cout << pokemon.name << " Lv " << pokemon.level << endl;
    
    cout << typeStrings[pokemon.type1];
    if (pokemon.type2 != NoType)
        cout << "/" << typeStrings[pokemon.type2];
    cout << endl;
    
    cout << "Item: " << itemStrings[pokemon.item] << endl;
    
    cout << "Ability: " << abilityStrings[pokemon.ability] << endl;
    
    cout << "Base Stats:" << endl;
    
    for (int i = 0; i < 6; i++)
        cout << statFullStrings[i] << ": " << pokemon.stats[i] << endl;
    
    if (pokemon.description != "")
        cout << pokemon.description << endl;
}

void Battle::pokeMoveInfo(const PokeData pokemon) const
{
    ostringstream o;
    
    int moveID;
    
    for (int i = 0; i < 4; i++)
    {
        moveID = pokemon.moveIDs[i];
        MoveData m = movelib[moveID];
        o << m.name << endl
        
        << "Type: " << typeStrings[m.type] << " Damage: ";
        
        if (m.damage == -1)
            o << '-';
        else
            o << m.damage;
        
        o << " Accuracy: ";
        
        if (m.accuracy == -1)
            o << '-';
        else
            o << m.accuracy;
        
        o << " ";
        
        if (m.moveType == Physical || m.moveType == Special)
            o << "Attack: ";
        else
            o << "Move: ";
        
        o << moveTypeStrings[m.moveType] << endl;
    }
    
    cout << o.str();
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
    << " would like to battle!" << endl;
}

void Battle::clockworkTick()
{
    m_turns++;
    
    for (int i = 0; i < NUMPLAYERS; i++)
        m_participants[i]->getPokemon()->tick();
}

void Battle::cycle()
{
    for (;; clockworkTick())
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
        
        if (m_actor->getPokemon() == NULL || m_actor->getPokemon()->isDead())
            // Replace fainted Pokemon
        {
            replacePokemon(m_actor);
            m_field->getSide(i)->getSlot()->fillSlot(m_actor->getPokemon());
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
    
    Pokemon* pokemon;
    
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = m_participants[i];
        
        if (m_actor->getIntendedMove() == SWITCH)
        {
            m_actor->switchPokemon(true);
            summonEffects();
            
            m_field->getSide(i)->getSlot()->fillSlot(m_actor->getPokemon());
        }
    }
    
    // Event before battle phase (i.e. item/Mega Evolution)
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
    
    // Do actions for certain moves (i.e. Focus Punch, Bide)
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = m_participants[i];
        int actorMove = m_actor->getIntendedMove();
        pokemon = m_actor->getPokemon();
        int moveID = pokemon->getIntendedMove();
        move = pokemon->getMove(moveID);
        
        if ((actorMove == FIGHT || actorMove == MEGA) && move->getEffect() == MFocusPunch)
        {
            cout << pokemon->getName() << " is tightening its focus!" << endl;
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
        
        if (pokemon->isDead())
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
                // Temporary targeting solution (ToDo)
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
                pokemon->getName() << " became confused"
                << " due to fatigue!" << endl;
                
                pokemon->addVStatus(ConfuseVStatus);
            }
        }
    }
}

void Battle::postBattlePhase()
{
    if (m_player->getIntendedMove() == RUN || m_player->getVictory() || m_opponent->getVictory() || checkWin())
        // Forfeit || battle has been won
        return;
    
    m_field->weatherContinue();
    checkDead();
    
    // TODO: implement item effects here and at other item-use points
    
    for (int i = 0; i < NUMPLAYERS; i++)
        statusEffect(m_participants[i]);
    
    checkDead();
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
            if (speedCompare(trainers[j]->getPokemon(), trainers[i]->getPokemon()) > 0)
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

int Battle::speedCompare(const Pokemon* pokemonA, const Pokemon* pokemonB) const
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
    Pokemon* pokemon;
    
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = m_participants[i];
        
        if (m_actor == m_player)
            // Choose player move
        {
            if (!m_actor->canChooseAction())
                continue;
            
            bool rerun = false;
            
            do
            {
                cout << "What would you like to do?" << endl;
                
                cout << "1: Fight!" << endl
                << "2: Bag" << endl
                << "3: Pokemon" << endl
                << "4: Run" << endl;
                
                int choice;
                cin >> choice;
                
                switch (choice)
                {
                    case 1:
                        rerun = !chooseFight();
                        break;
                    case 2:
                        rerun = !chooseBag();
                        break;
                    case 3:
                        rerun = !choosePokemon(m_player);
                        break;
                    case 4:
                        rerun = !chooseRun();
                        break;
                    default:
                        break;
                }
            }
            while (rerun);
            
            summonEffects();
        }
        else
            // Select opponent's move
        {
            // Level -1: Purposely choose bad moves*
            // Level 0: Simply make a random choice from 4 moves
            // Level 1: 1/3 chance to favor the best move
            // Level 2: 2/3 chance to favor the best move
            // Level 3: Always favor the best move
            // *Calculated using an algorithm that scores each move/switching out/etc.
            
            // Level 0 (no switching):
            pokemon = m_actor->getPokemon();
            
            if (pokemon->canMegaEvolve())
                m_actor->setIntendedMove(MEGA);
            else
                m_actor->setIntendedMove(FIGHT);
            
            pokemon->setIntendedMove(randInt(0, 3));
        }
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

bool Battle::replacePokemon(Trainer* trainer) const
{
    if (trainer == m_player)
    {
        return playerSummon(false);
    }
    else
    {
        opponentSummon(m_opponent, false);
        
        return true;
    }
}

bool Battle::playerSummon(bool optional) const
{
    int choice, i;
    bool rerun = false;
    Pokemon* pokemon;
    
    do
    {
        rerun = false;
        
        cout << "Choose a Pokemon:" << endl;
        
        cout << m_player->generateBalls() << endl;
        
        // Summon prompt
        for (i = 0; i < MAXPOKEMON; i++)
        {
            pokemon = m_player->getPokemon(i);
            
            if (pokemon == NULL)
                break;
            
            ostringstream oss;
                
            if (pokemon->getStatus() != HealthyStatus)
                oss << ": " << statusText(pokemon, false);
            
            if (m_player->getCurrent() == i && !pokemon->isDead())
                oss << ": In Battle";
            
            if (pokemon != NULL)
                cout << i+1 << ": " << pokemon->getName() << oss.str() << endl;
        }
        
        if (optional)
            cout << ++i << ": (Cancel)" << endl;
        
        cin >> choice;
        
        /*switch (choice)
        {
            default:
                rerun = true;
                continue;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                break;
            case 7:
                if (optional)
                    return false;
                else
                {
                    rerun = true;
                    continue;
                }
        }*/
        
        if (choice > 0 && choice <= i)
        {
            if (optional && choice == i)
                return false;
        }
        else
        {
            rerun = true;
            continue;
        }
        
        // Useful?
        if (m_player->getPokemon(choice-1) == NULL)
        {
            rerun = true;
            continue;
        }
        
        int choicee;
        bool rerunn = false;
        
        do
        {
            rerunn = false;
            rerun = false;
            
            cout << "What to do with " << m_player->getPokemon(choice-1)->getName() << "?" << endl << "1: Switch" << endl << "2: Summary" << endl << "3: Check Moves" << endl << "4: (Cancel)" << endl;
            
            cin >> choicee;
            
            switch (choicee)
            {
                default:
                    rerunn = true;
                    continue;
                case 1:
                    if (m_player->getPokemon(choice-1)->isDead())
                    {
                        cout << m_player->getPokemon(choice-1)->getName() << " is fainted and cannot battle." << endl;
                        rerunn = true;
                    }
                    else if (m_player->getCurrent() == choice-1)
                    {
                        cout << m_player->getPokemon(choice-1)->getName() << " is already out!" << endl;
                        rerunn = true;
                    }
                    break;
                case 2:
                    printPokeInfo(choice-1);
                    rerunn = true;
                    break;
                case 3:
                    printPokeMoves(choice-1);
                    rerunn = true;
                    break;
                case 4:
                    rerun = true;
                    rerunn = false;
                    break;
            }
            
        } while (rerunn);
        
    }
    while (rerun);
    
    m_player->setIntendedSwitch(choice-1);

    if (optional)
        m_player->setIntendedMove(SWITCH);
    else
        m_player->switchPokemon(false);
    
    return true;
}

void Battle::opponentSummon(Trainer* trainer, bool optional) const
{
    int pokemonLeft = 0;
    
    for (int i = 0; i < MAXPOKEMON; i++)
    {
        if (trainer->getPokemon(i) != NULL && !trainer->getPokemon(i)->isDead())
        {
            pokemonLeft++;
        }
    }
    
    int choice = randInt(0, pokemonLeft-1);
    
    for (int i = 0; i < MAXPOKEMON; i++)
    {
        if (trainer->getPokemon(i) != NULL && !trainer->getPokemon(i)->isDead())
        {
            if (choice == 0)
            {
                m_opponent->setIntendedSwitch(i);
                
                if (optional)
                    m_opponent->setIntendedMove(SWITCH);
                else
                    m_opponent->switchPokemon(false);
                
                break;
            }
            else
                choice--;
        }
    }
}

void Battle::turnCount() const
{
    ostringstream o;
    
    if (m_field->getWeather() != NoWeather)
        o << " (" << weatherStrings[m_field->getWeather()] << ")";
    
    cout << "Turn " << m_turns+1 << o.str() << endl;
}

void Battle::statusEffect(Trainer* trainer) const
{
    Pokemon* pokemon = trainer->getPokemon();
    
    pokemon->removeShortStatus();
    
    if (pokemon->isDead())
        return;
    
    if (pokemon->getStatus() == BurnStatus)
    {
        cout << trainer->getTitle() << " " << trainer->getName()
        << "'s " << pokemon->getName() << " is hurt by its burn!" << endl;
        pokemon->lowerHP(static_cast<double>(pokemon->getBStats(HPSTAT)) * (0.125));
    }
    else if (pokemon->getStatus() == PoisonStatus)
    {
        cout << trainer->getTitle() << " " << trainer->getName() << "'s "
        << pokemon->getName() << " is hurt by poison!" << endl;
        pokemon->lowerHP(static_cast<double>(pokemon->getBStats(HPSTAT)) * (0.125));
    }
    else if (pokemon->getStatus() == ToxicStatus)
    {
        pokemon->setToxicTurns(pokemon->getToxicTurns()+1);
        cout << trainer->getTitle() << " " << trainer->getName() << "'s "
        << pokemon->getName() << " is hurt by poison!" << endl;
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
        
        for (int i = ATTSTAT; i < NUMSTATS; i++)
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
    int healAmount;
    
    int sc[6] = { 0, 0, 0, 0, 0, 0 };
    
    if (me == MHeal50)
        // Calculate heal amount
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
    
    switch (me)
    {
        case MHeal50:
            cout << trainerB->getTitle() << " " << trainerB->getName() << "'s " << target->getName();
            if (target->increaseHP(healAmount))
                cout << "'s HP was restored!";
            else
                cout << "'s HP can't go any higher!";
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
    
    for (int i = ATTSTAT; i < NUMSTATS; i++)
    {
        if (sc[i] < 0)
        {
            if (sc[i] == -1)
                target->lowerStat(i, false);
            else
                target->lowerStat(i, -sc[i]);
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
    specialDefMultiplier, specialDefPierce, defPierce, modifier, spOrNot,
    damage, totalDamage;
    
    int critThreshold;
    
    if (target->hasVStatus(ProtectVStatus) || target->hasVStatus(ShieldVStatus))
    {
        target->protectDialogue();
        
        if (target->hasVStatus(ShieldVStatus))
        {
            if (attackMove->getContact())
                attacker->lowerStat(ATTSTAT, 2);
        }
        
        return;
    }
    
    if (target->getAbility() == PLevitate && attackMove->getType() == GroundType)
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
        cout << "It doesn't affect " << trainerB->getTitle() << ' '
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
    
    if (attacker->getAbility() == PHugePower || attacker->getAbility() == PPurePower)
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
        specialDefMultiplier *= (target->getType1() == RockType ||
                                 target->getType2() == RockType) ? 1.5 : 1.0;
    }
    else if (m_field->getWeather() == Hail)
    {
        
    }
    
    if (attackMove->getEffect() == MIgnoreDef100)
        // Move pierces defense
    {
        defPierce = static_cast<double>(target->getBStats(DEFSTAT) *
                    attacker->statMultiplier(-6)) /
                    static_cast<double>(target->getStats(DEFSTAT));
        specialDefPierce = static_cast<double>(target->getBStats(SPDSTAT) *
                            attacker->statMultiplier(-6)) /
                            static_cast<double>(target->getStats(SPDSTAT));
    }
    else
    {
        defPierce = 1.0;
        specialDefPierce = 1.0;
    }
    
    modifier = typeBoost * sTAB * crit * modulus * other;
    
    if (trainerA->getPokemonMove(whichMove)->getMoveType() == Physical)
        // Physical attack
    {
        spOrNot = static_cast<double>(attacker->getStats(ATTSTAT) *
                attackMultiplier) / static_cast<double>(target->getStats(DEFSTAT) *
                defPierce);
    }
    else
        // Special attack
    {
        spOrNot = static_cast<double>(attacker->getStats(SPASTAT)) /
        (static_cast<double>(target->getStats(SPDSTAT) * specialDefMultiplier *
        specialDefPierce));
    }
    
    damage = (((2.0 * attacker->getOnMyLevel() + 10.0) / 250.0) *
              (spOrNot) * pureDamage + 2.0);
    
    totalDamage = damage * modifier;
    
    if (attackMove->getEffect() == MOHKO)
        totalDamage = target->getStats(HPSTAT);
    else if (attackMove->getEffect() == MDamage20)
        totalDamage = 20;
    else if (attackMove->getEffect() == MDamage40)
        totalDamage = 40;
    else if (attackMove->getEffect() == MDamageLevel)
        totalDamage = attacker->getOnMyLevel();
    
    target->lowerHP(totalDamage);
    
    if (crit == 1.50)
        cout << "A critical hit!" << endl;
    
    if (typeBoost > 1.0)
        cout << "It's super effective!" << endl;
    else if (typeBoost < 1.0)
        cout << "It's not very effective..." << endl;
    
    if (attackMove->getEffect() == MOHKO)
        // OHKO move that hit (since it made it here)
        cout << "It's a one-hit KO!" << endl;
    
    applyEffect(trainerA, trainerB, whichMove);
}

void Battle::applyEffect(Trainer* trainerA, Trainer* trainerB, int whichMove) const
{
    Pokemon* attacker = trainerA->getPokemon();
    Pokemon* target = trainerB->getPokemon();
    Move* attackMove = attacker->getMove(whichMove);
    MoveEffect effect = attackMove->getEffect();
    
    // Attacker side-effects (successful move execution)
    
    if (effect == MRampage && attackMove->isThrash() && attacker->getRampageTurns() == 0)
        // Thrash-style rampage
    {
        attacker->addVStatus(RampageVStatus);
        attacker->setRampageTurns(randInt(2, 3));
    }
    
    if (effect == MOverheat)
        // Overheat effect
    {
        attacker->lowerStat(SPASTAT, 2);
    }
    
    if (effect == MFocusPunch)
        // Focus punch
        attacker->removeVStatus(FocusVStatus);
    
    // Target side-effects (successfully hit)
    
    if (target->isDead() || target->getStats(HPSTAT) == 0)
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
    
    if (effect == MPoison10 || effect == MPoison15 || effect == MPoison30 || effect == MPoison40)
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
    
    if (effect == MParalyze10 || effect == MParalyze15 || effect == MParalyze30 || effect == MParalyze100)
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

void Battle::checkDead() const
{
    for (int i = 0; i < NUMPLAYERS; i++)
        m_participants[i]->checkDead();
}

Trainer* Battle::getParticipants(int i) const
{
    return m_participants[i];
}

bool Battle::chooseFight()
{
    Pokemon* pokemon = m_player->getPokemon();
    
    int playerChoice, j;
    bool canMega, willMegaEvolve = false;
    
    do
    {
        cout << "Select a move:" << endl;
        
        for (j = 0; j < MAXMOVES; j++)
        {
            cout << j+1 << ": ";
            
            cout << m_player->getPokemonMove(j)->getName() << endl;
        }
        
        canMega = pokemon->canMegaEvolve();
        
        if (canMega)
        {
            cout << ++j << ": *Mega Evolution*";
            
            if (willMegaEvolve)
                cout << " (Selected)";
            
            cout << endl;
        }
        
        cout << ++j << ": (Move Info)" << endl;
        cout << ++j << ": (Cancel)" << endl;
        
        cin >> playerChoice;
        
        if (playerChoice == j-1)
            printMoveInfo();
        
        if (canMega && playerChoice == 5)
        {
            if (willMegaEvolve)
            {
                willMegaEvolve = false;
            }
            else
            {
                willMegaEvolve = true;
            }
            
            playerChoice = j-1;
        }
        
    } while (playerChoice == j-1);
    
    switch (playerChoice)
    {
        default:
            return false;
        case 1:
        case 2:
        case 3:
        case 4:
            if (!willMegaEvolve)
                m_player->setIntendedMove(FIGHT);
            else
                m_player->setIntendedMove(MEGA);
            break;
    }
    
    pokemon->setIntendedMove(playerChoice-1);
    
    return true;
}

void Battle::printMoveInfo() const
{
    Move* move;
    
    for (int i = 0; i < MAXMOVES; i++)
    {
        move = m_player->getPokemonMove(i);
        
        ostringstream pout;
        
        string pOS;
        if (move->getMoveType() == Status)
            pOS = "Move: Status";
        else
        {
            if (move->getMoveType() == Physical)
                pOS = "Attack: Physical";
            else
                pOS = "Attack: Special";
        }
        
        pout << move->getName() << endl << "Type: "
        << typeStrings[typeNumber(move->getType())] << " Damage: ";
        
        if (move->getDamage() == -1)
            pout << '-';
        else
            pout << move->getDamage();
        
        pout << " Accuracy: ";
        
        if (move->getAccuracy() == -1)
            pout << '-';
        else
            pout << move->getAccuracy();
        
        pout << " " << pOS;
        
        cout << pout.str() << endl;
        
        if (!(move->getDescription() == ""))
            cout << move->getDescription() + '\n';
    }
}

bool Battle::chooseBag() const
{
    // No bag implementation since focus is on competitive
    // (no using items, among other things) battling
    cout << "You can't do that right now." << endl;
    
    return false;
}

bool Battle::chooseRun() const
{
    cout << "Are you sure you'd like to run and forfeit the match?" << endl;
    
    cout << "1: Yes" << endl << "2: No" << endl;
    
    int choice;
    cin >> choice;
    
    switch (choice)
    {
        case 1:
            cout << m_player->getTitle() << " " << m_player->getName() << " has forfeited the match." << endl;
            m_opponent->setVictory();
            m_player->setIntendedMove(RUN);
            return true;
        default:
            break;
    }
    
    return false;
}

Trainer* Battle::getPlayer() const
{
    return m_player;
}

Trainer* Battle::getOpponent() const
{
    return m_opponent;
}

void Battle::printPokeInfo(int slotNumber) const
{
    Pokemon* pokemon = m_player->getPokemon(slotNumber);
    
    ostringstream pout;
    
    string slasher = "/";
    string description = "\n";
    
    pout << pokemon->getName() << " Lv "
    << pokemon->getOnMyLevel() << " " << ((pokemon->getGender() == Male) ? "M" : (pokemon->getGender() == Female) ? "F" : " ") << statusText(pokemon, false) << endl
    
    << typeStrings[pokemon->getType1()] << ((pokemon->getType2() != NoType) ? slasher + typeStrings[pokemon->getType2()] : "") << endl
    
    << "Item: " << itemStrings[pokemon->getItem()->getID()] << endl
    
    << "Ability: " << abilityStrings[pokemon->getAbility()] << endl
    << "Nature: " << natureStrings[pokemon->getNature()] << endl
    
    << "HP: " << pokemon->getStats(HPSTAT) << '/' << pokemon->getBStats(HPSTAT) << endl;
    
    for (int i = ATTSTAT; i < NUMSTATS; i++)
        pout << statFullStrings[i] << ": " << pokemon->getBStats(i) << endl;
    
    pout << ((pokemon->getDescription() != "") ? pokemon->getDescription() : "") << endl;
    
    cout << pout.str();
}

void Battle::printPokeMoves(int pokemon) const
{
    Move* move;
    
    for (int i = 0; i < MAXMOVES; i++)
    {
        move = m_player->getPokemon(pokemon)->getMove(i);
        
        ostringstream pout;
        
        string pOS;
        if (move->getMoveType() == Status)
            pOS = "Move: Status";
        else
        {
            if (move->getMoveType() == Physical)
                pOS = "Attack: Physical";
            else
                pOS = "Attack: Special";
        }
        
        pout << move->getName() << endl << "Type: " << typeStrings[typeNumber(move->getType())] << " Damage: ";
        
        if (move->getDamage() == -1)
            pout << '-';
        else
            pout << move->getDamage();
        
        pout << " Accuracy: ";
        
        if (move->getAccuracy() == -1)
            pout << '-';
        else
            pout << move->getAccuracy();
        
        pout << " " << pOS;
        
        cout << pout.str() << endl;
        
        cout << ((move->getDescription() == "") ? "" : move->getDescription() + '\n');
    }
}

bool Battle::choosePokemon(Trainer* trainer) const
{
    if (trainer == m_player)
    {
        return playerSummon(true);
    }
    else
    {
        opponentSummon(m_opponent, true);
        
        return true;
    }
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
        if (m_player->getPokemon(i) != NULL && !m_player->getPokemon(i)->isDead())
            opponentWon = false;
        
        if (m_opponent->getPokemon(i) != NULL && !m_opponent->getPokemon(i)->isDead())
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
        cout << "The match was a draw!" << endl;
    }
    else if (m_player->getVictory())
    {
        cout << m_player->getTitle() << " " << m_player->getName() << " won the battle!" << endl << "Got $" << m_opponent->getReward()
        << " for winning!" << endl;
    }
    else if (m_opponent->getVictory())
    {
        cout << m_opponent->getTitle() << " " << m_opponent->getName() << " won the battle!" << endl;
    }
}