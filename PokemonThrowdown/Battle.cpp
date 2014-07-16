//
//  Battle.cpp
//  pokemongame
//
//  Created by Ian Cordero on 3/3/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Battle.h"
#include "Trainer.h"
#include "trainerdata.h"
#include "constants.h"
#include "strings.h"
#include "pokedata.h"
#include "movedata.h"
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
    
    // Zero out variables
    m_player = NULL;
    m_player2 = NULL;
    m_opponent = NULL;
    m_opponent2 = NULL;
    m_turns = 0;
    m_actor = NULL;
    m_numPlayers = 0;
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
        
        if (!m_actor->isComputer())
        {
            do
            {
                cout << "Choose lead Pokemon" << ":" << endl;
                
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
    trainerdata protoman;
    
    int choice[4] = { -1, -1, -1, -1 };
    int pokemonID;
    
    do
    {
        cout << "Choose" << " ";
        if (m_numPlayers == 0)
            cout << "a trainer";
        else
            cout << "an opponent";
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
            cout << "You chose" << " " << trainerlib[choice[0]-1].title
            << " " << trainerlib[choice[0]-1].name << "." << endl;
            
            cout << "1: " << "Confirm" << endl
                 << "2: " << "Pokemon" << endl
                 << "3: " << "(" << "Back" << ")" << endl;
            
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
                cout << "7: " << "(" << "Back" << ")" << endl;
                
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
                    
                    cout << "You chose" << " "
                    << pokelib[pokemonID].name << "."
                    << endl;
                    cout << "1: " << "Summary" << endl
                         << "2: " << "Check Moves" << endl
                         << "3: " << "(" << "Back" << ")" << endl;
                    
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
    if (m_numPlayers == 0)
    {
        m_player = new Player(protoman, this);
        setPlayer(m_player);
        m_field->getSide(0)->addTrainer(m_player);
    }
    else // m_numPlayers > 1
    {
        m_opponent = new Computer(protoman, this);
        setOpponent(m_opponent);
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
    cout << m_opponent->getTitleName()
    << " " << "would like to battle!" << endl;
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
        
        if (m_actor->getIntendedMove() == SwitchDecision)
        {
            // Replace fainted Pokemon
            m_actor->switchPokemon(false);
            m_field->getSide(i)->getSlot()->fillSlot(m_actor->getPokemon());
            
            m_actor->setIntendedMove(NoDecision);
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
    if (m_player->getIntendedMove() == RunDecision)
        // Forfeit
        return;
    
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        m_actor = m_participants[i];
        
        if (m_actor->getIntendedMove() == SwitchDecision)
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
    if (m_player->getIntendedMove() == RunDecision)
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
        
        priorityScore[i] = move->getPriorityScore();
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
        
        if (m_actor->getIntendedMove() == MegaDecision)
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
        
        if ((actorMove == FightDecision || actorMove == MegaDecision)
            && move->getEffect() == MFocusPunch)
        {
            cout << pokemon->getName() << " " << "is tightening its focus!" << endl;
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
        
        if (actorMove == SwitchDecision || actorMove == BagDecision)
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
                pokemon->getName() << " " << "became confused due to fatigue!" << endl;
                
                pokemon->addVStatus(ConfuseVStatus);
            }
        }
    }
}

void Battle::postBattlePhase()
{
    if (m_player->getIntendedMove() == RunDecision || m_player->getVictory()
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
        m_participants[i]->setIntendedMove(NoDecision);
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

    efSA = pokemonA->getStats(SpeStat) * smA;
    efSB = pokemonB->getStats(SpeStat) * smB;
    
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
    
    cout << "Turn" << " " << m_turns+1 << o.str() << endl;
}

void Battle::statusEffect(Trainer* trainer) const
{
    Pokemon* pokemon = trainer->getPokemon();
    
    pokemon->removeShortStatus();
    
    if (pokemon->isFainted())
        return;
    
    if (pokemon->getStatus() == BurnStatus)
    {
        cout << trainer->getTitleName()
        << "'s " << pokemon->getName() << " " << "is hurt by its burn!" << endl;
        pokemon->lowerHP(static_cast<double>(pokemon->getBStats(HPStat))
                         * (0.125));
    }
    else if (pokemon->getStatus() == PoisonStatus)
    {
        cout << trainer->getTitleName() << "'s "
        << pokemon->getName() << " " << "is hurt by poison!" << endl;
        pokemon->lowerHP(static_cast<double>(pokemon->getBStats(HPStat))
                         * (0.125));
    }
    else if (pokemon->getStatus() == ToxicStatus)
    {
        pokemon->setToxicTurns(pokemon->getToxicTurns()+1);
        cout << trainer->getTitleName() << "'s "
        << pokemon->getName() << " " << "is hurt by poison!" << endl;
        pokemon->lowerHP(static_cast<double>(pokemon->getBStats(HPStat)) *
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
        
        for (int i = AttStat; i < NUMALLSTATS; i++)
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
        cout << "The match was a draw!" << endl;
    }
    else if (m_player->getVictory())
    {
        cout << m_player->getTitleName() << " "
        << "won the battle!" << endl << "Got" << " $"
        << m_opponent->getReward() << " " << "for winning!" << endl;
    }
    else if (m_opponent->getVictory())
    {
        cout << m_opponent->getTitleName() << " "
        << "won the battle!" << endl;
    }
}

void Battle::dispPokeSummary(int slotNumber) const
{
    ostringstream pout;
    Pokemon* pokemon = m_player->getPokemon(slotNumber);
    
    // Name
    pout << pokemon->getName() << " "
    // Level
    << "Lv" << " " << pokemon->getLevel() << " "
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
    pout << "Item" << ": " << itemStrings[pokemon->getItem()->getID()]
    << endl
    
    // Ability
    << "Ability" << ": " << abilityStrings[pokemon->getAbility()] << endl
    
    // Nature
    << "Nature" << ": " << natureStrings[pokemon->getNature()] << endl
    
    // Stats
    << statFullStrings[HPStat] << ": " << pokemon->getStats(HPStat) << '/'
    << pokemon->getBStats(HPStat) << endl;
    for (int i = AttStat; i < NUMSTATS; i++)
        pout << statFullStrings[i] << ": " << pokemon->getBStats(i) << endl;
    
    // Description
    if (pokemon->getDescription() != "")
        pout << pokemon->getDescription();
    pout << endl;
    
    cout << pout.str();
}

void Battle::dispPokeSummary(const pokedata pokemon) const
{
    // Name
    cout << pokemon.name << " "
    // Level
    << "Lv" << " " << pokemon.level << endl;
    
    // Type
    cout << typeStrings[pokemon.type1];
    if (pokemon.type2 != NoType)
        cout << "/" << typeStrings[pokemon.type2];
    cout << endl;
    
    // Item
    cout << "Item" << ": " << itemStrings[pokemon.item] << endl;
    
    // Ability
    cout << "Ability" << ": " << abilityStrings[pokemon.ability[0]] << endl;
    
    // Stats
    cout << "Base Stats" << ":" << endl;
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
            pOS += "Move";
            pOS += ": ";
            pOS += moveTypeStrings[Status];
        }
        else
        {
            pOS += "Attack";
            pOS += ": ";
            
            if (move->getMoveType() == Physical)
                pOS += moveTypeStrings[Physical];
            else
                pOS += moveTypeStrings[Special];
        }
        
        pout << move->getName() << endl << "Type" << ": "
        << typeStrings[move->getType()] << " " << "Damage"
        << ": ";
        
        if (move->getDamage() == -1)
            pout << '-';
        else
            pout << move->getDamage();
        
        pout << " " << "Accuracy" << ": ";
        
        if (move->getAccuracy() == -1)
            pout << '-';
        else
            pout << move->getAccuracy();
        
        pout << " " << pOS;
        
        if (move->getDescription() != "")
            pout << endl << move->getDescription();
        
        cout << pout.str() << endl;
    }
}

void Battle::dispPokeMoves() const
{
    dispPokeMoves(0);
}

void Battle::dispPokeMoves(const pokedata pokemon) const
{
    ostringstream o;
    
    int moveID;
    
    for (int i = 0; i < 4; i++)
    {
        moveID = pokemon.moveIDs[i];
        movedata m = movelib[moveID];
        o << m.name << endl
        
        << "Type" << ": " << typeStrings[m.type] << " "
        << "Damage" << ": ";
        
        if (m.damage == -1)
            o << '-';
        else
            o << m.damage;
        
        o << " " << "Accuracy" << ": ";
        
        if (m.accuracy == -1)
            o << '-';
        else
            o << m.accuracy;
        
        o << " ";
        
        if (m.moveType == Physical || m.moveType == Special)
            o << "Attack" << ": ";
        else
            o << "Move" << ": ";
        
        o << moveTypeStrings[m.moveType] << endl;
        
        if (m.description != "")
            o << m.description << endl;
    }
    
    cout << o.str();
}

bool Battle::setPlayer(Trainer* player)
{
    if (m_participants[0] != NULL)
        return false;
    else
    {
        setParticipants(player);
        return true;
    }
}

bool Battle::setOpponent(Trainer* opponent)
{
    if (m_participants[m_numPlayers] != NULL)
        return false;
    else
    {
        setParticipants(opponent);
        return true;
    }
}

bool Battle::setParticipants(Trainer* participant)
{
    if (m_participants[m_numPlayers] != NULL)
        return false;
    else
    {
        m_participants[m_numPlayers++] = participant;
        return true;
    }
}
