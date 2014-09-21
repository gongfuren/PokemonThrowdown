//
//  Game.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 9/6/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Game.h"
#include <sstream>
#include <vector>
#include "Battle.h"
#include "strings.h"
#include "pokedata.h"
#include "movedata.h"
#include "constants.h"
#include "utilities.h"
#include "Settings.h"
using namespace std;

// Core Game Functions ///////////////////////////////////////////////////////

void Game::titleScreen()
{
    printTitle();
    
    cout << "Press START to begin!" << endl;
    
    confirmGadget("START");
}

void Game::loadingScreen()
{
    cout << "Loading..." << endl;
    
    if (!getSettings()->loadSettings())
        cout << "Oops! Something seems to have went wrong." << endl;
}

void Game::mainMenu()
{
    bool rerun = true;
    int prog = 0;
    const int numOpts = 4;
    string opts[numOpts] = { "Play!", "Settings", "Guide", "Quit" };
    
    while (rerun)
    {
        printTitle(-1);
        
        switch (selectorGadget(opts, numOpts, prog, numOpts, false))
        {
            case 0:
                startBattle();
                break;
            case 1:
                getSettings()->configureSettings();
                break;
            case 2:
                guideBook();
                break;
            default:
                rerun = false;
                break;
        }
    }
}

// Helper Functions //////////////////////////////////////////////////////////

void Game::startBattle()
{
    Battle b(this);
    
    if (!b.configure())
        return;
    
    b.start();
}

void Game::guideBook()
{
    bool rerun = true;
    int prog = 0;
    const int numOpts = 5;
    string gopts[numOpts] = { "Pokedex", "Movedex", "Typedex", "Credits", "Help" };
    
    while (rerun)
    {
        cout << "Guide Book:" << endl;
        
        switch (selectorGadget(gopts, numOpts, prog))
        {
            case 0:
                pokeMoveDex();
                break;
            case 1:
                pokeMoveDex(true);
                break;
            case 2:
                displayTypes();
                break;
            case 3:
                displayCredits();
                break;
            case 4:
                displayHelp();
                break;
            default:
                rerun = false;
                break;
        }
    }
}

// Secondary Helper Functions

void Game::displayTypes()
{
    bool rerun = true;
    int prog = 0;
    const int numOpts = MAXTYPES-1;
    string topts[numOpts];
    
    for (int i = 0; i < numOpts; i++)
        topts[i] = typeStrings[i+1];
    
    while (rerun)
    {
        cout
        << "0-------------------0" << endl
        << "| Typedex  [ +-x/% ]|" << endl
        << "0-------------------0" << endl
        << "|/+---------------+/|" << endl
        << "| |.:.:.:.:.:.:.:.| |" << endl
        << "|/+---------------+/|" << endl
        << "O-------------------O" << endl;
        
        int choice = selectorGadget(topts, numOpts, prog);
        
        switch (choice)
        {
            default:
                typeSummary(choice+1);
                break;
            case BACK:
                rerun = false;
                break;
        }
    }
}

void Game::displayCredits()
{
    cout << "Credits:" << endl;
    
    cout << "Pokemon Throwdown" << endl;
    
    cout << "An originally-coded Pokemon simulator that is true to the game." << endl
    
    << "All credit goes to Nintendo for original game design, mechanics, etc." << endl
    
    << "Made by a huge fan." << endl;
    
    cout << "throwdown (n.) informal" << endl
    << "a performance by or competition between rappers, breakdancers, etc." << endl
    << "ex: a funky hip-hop throwdown." << endl;
    
    cout << "Pokemon \"Throwdown\" is a play on the popular web-based Pokemon Showdown battle\nsimulator." << endl
    
    << "(C) 2013-2014 Ian P. Cordero." << endl;
    // Contributors feel free to add your names here.
    
    confirmGadget();
}

void Game::displayHelp()
{
    int prog = 0;
    const int numOpts = 1;
    string hopts[numOpts] = { "Command Line Interface" };
    
    while (true)
    {
        cout << "Help:" << endl;
        
        switch (selectorGadget(hopts, numOpts, prog))
        {
            case 0:
            {
                cout << "Command Line Options Breakdown:" << endl
                << "-d" << endl
                << "    Disable save file capability (team export will still be available)." << endl;
                confirmGadget();
            }
                break;
            default:
                return;
        }
    }
}

void Game::typeSummary(int whichType)
{
    bool rerun = true;
    int prog = 0;
    const int numOpts = 4;
    string topts[numOpts] = { "Offense", "Defense", "Pokemon", "Moves" };
    
    while (rerun)
    {
        cout << typeStrings[whichType] << " Type:" << endl;
        
        switch (selectorGadget(topts, numOpts, prog))
        {
            case 0:
                cout << "Offense against:" << endl;
                
                for (int i = 1; i < MAXTYPES; i++)
                {
                    cout << "   " << typeStrings[i] << ": x" << typeMultiplier(static_cast<Type>(whichType), static_cast<Type>(i)) << endl;
                }
                confirmGadget();
                break;
            case 1:
                cout << "Defense against:" << endl;
                
                for (int i = 1; i < MAXTYPES; i++)
                {
                    cout << "   " << typeStrings[i] << ": x" << typeMultiplier(static_cast<Type>(i), static_cast<Type>(whichType)) << endl;
                }
                confirmGadget();
                break;
            case 2:
                cout << "Pokemon with the " << typeStrings[whichType] << " type:" << endl;
                for (int i = 1; i < MAXNUMPOKEMON; i++)
                    if (pokelib[i].type1 == whichType || pokelib[i].type2 == whichType)
                        cout << pokelib[i].name << " (#" << pokelib[i].ID << ") (" << typeStrings[pokelib[i].type1] << ((pokelib[i].type2 == NoType) ? "" : "/") << ((pokelib[i].type2 == NoType) ? "" : typeStrings[pokelib[i].type2]) << ")" << endl;
                confirmGadget();
                break;
            case 3:
                cout << typeStrings[whichType] << " type Moves:" << endl;
                for (int i = 1; i < MAXNUMMOVES; i++)
                    if (movelib[i].type == whichType)
                        cout << movelib[i].name << " (#" << movelib[i].ID << ") (" << typeStrings[movelib[i].type] << ")" << endl;
                confirmGadget();
                break;
            default:
                rerun = false;
                break;
        }
    }
}

void Game::pokeMoveDexBrowse(bool moves)
{
    int prog = 0;
    const int numOpts = (moves ? MAXNUMMOVES : MAXNUMPOKEMON)-1;
    string* popts = new string[numOpts];
    
    for (int i = 0; i < numOpts; i++)
    {
        ostringstream tmp;
        tmp << (moves ? movelib[i+1].name : pokelib[i+1].name) << " (#" << (moves ? movelib[i+1].ID : pokelib[i+1].ID) << ")";
        popts[i] = tmp.str();
    }
    
    while (true)
    {
        cout << "Browse:" << endl;
        
        int choice = selectorGadget(popts, numOpts, prog);
        
        if (choice == BACK)
        {
            delete[] popts;
            return;
        }
        else
        {
            if (moves)
            {
                cout << movelib[choice+1].name << endl;
                choseMoveInfo(choice+1);
            }
            else
                chosePokemonInfo(choice+1);
            
            confirmGadget();
        }
    }
    
    delete[] popts;
}

void Game::pokeMoveDexSearch(bool moves)
{
    int prog = 0;
    const int numOpts = moves ? MAXNUMMOVES : MAXNUMPOKEMON;
    vector<int> matches;
    string buffer;
    
    while (true)
    {
        cout << "Enter search term (type \":q\" to cancel search):" << endl;
        getline(cin, buffer);
        
        if (buffer == ":q")
            return;
        else
        {
            for (int i = 1; i < numOpts; i++)
            {
                string candidate = (moves ? movelib[i].name : pokelib[i].name), term = buffer;
                
                for (int j = 0; j < candidate.length(); j++)
                    candidate[j] = tolower(candidate[j]);
                for (int j = 0; j < term.length(); j++)
                    term[j] = tolower(term[j]);
                
                if (candidate.find(term) != -1)
                    matches.push_back(i);
            }
            
            if (matches.empty())
            {
                cout << "No " << (moves ? "Moves" : "Pokemon") << " match the search terms!" << endl;
                continue;
            }
            
            string* matchStrings = new string[matches.size()];
            
            for (int i = 0; i < matches.size(); i++)
            {
                ostringstream tmp;
                tmp << (moves ? movelib[matches[i]].name : pokelib[matches[i]].name) << " (#" << (moves ? movelib[matches[i]].ID : pokelib[matches[i]].ID) << ")";
                matchStrings[i] = tmp.str();
            }
            
            while (true)
            {
                int choice = selectorGadget(matchStrings, static_cast<int>(matches.size()), prog);
                
                if (choice == BACK)
                    break;
                
                if (moves)
                {
                    cout << movelib[matches[choice]].name << endl;
                    choseMoveInfo(matches[choice]);
                }
                else
                    chosePokemonInfo(matches[choice]);
                
                confirmGadget();
            }
            
            delete[] matchStrings;
            matches.clear();
        }
    }
}

void Game::pokeMoveDexRandom(bool moves)
{
    int pokeMoveID = randInt(1, moves ? MAXNUMMOVES : MAXNUMPOKEMON);
    
    if (moves)
    {
        cout << movelib[pokeMoveID].name << endl;
        choseMoveInfo(pokeMoveID);
    }
    else
        chosePokemonInfo(pokeMoveID);
    
    confirmGadget();
}

void Game::pokeMoveDex(bool moves)
{
    int prog = 0;
    const int numOpts = 3;
    
    string copts[numOpts] = { "Browse", "Search", "Random" };
    
    while (true)
    {
        cout
        << "0-------------------0" << endl
        << "| " << (moves ? "Movedex" : "Pokedex") << "  [ " << (moves ? "/\\/\\/" : "(-o-)") << " ]|" << endl
        << "0-------------------0" << endl
        << "|/+---------------+/|" << endl
        << "| |.:.:.:.:.:.:.:.| |" << endl
        << "|/+---------------+/|" << endl
        << "O-------------------O" << endl;
        
        switch (selectorGadget(copts, numOpts, prog))
        {
            case 0:
                pokeMoveDexBrowse(moves);
                break;
            case 1:
                pokeMoveDexSearch(moves);
                break;
            case 2:
                pokeMoveDexRandom(moves);
                break;
            default:
                return;
        }
    }
}

void Game::printTitle(int whichTitle)
{
    switch (whichTitle)
    {
        case 0:
            cout << "__________       __\n\\______   \\____ |  | __ ____   _____   ____   ____\n |     ___/  _ \\|  |/ // __ \\ /     \\ /  _ \\ /    \\\n |    |  (  <_> )    <\\  ___/|  Y Y  (  <_> )   |  \\\n |____|   \\____/|__|_ \\\\___  >__|_|  /\\____/|___|  /\n                     \\/    \\/      \\/            \\/\n___________.__                           .___\n\\__    ___/|  |_________  ______  _  ____| _/______  _  ______\n  |    |   |  |  \\_  __ \\/  _ \\ \\/ \\/ / __ |/  _ \\ \\/ \\/ /    \\\n  |    |   |   Y  \\  | \\(  <_> )     / /_/ (  <_> )     /   |  \\\n  |____|   |___|  /__|   \\____/ \\/\\_/\\____ |\\____/ \\/\\_/|___|  /\n                \\/                        \\/                 \\/" << endl;
            cout << "                                                         " << VERSIONNUMBER << endl;
            break;
        case 1:
            cout << " (                                                 \n )\\ )       )                                      \n(()/(    ( /(   (    )                             \n /(_))(  )\()) ))\\  (     (   (                    \n(_))  )\((_)\\ /((_) )\\  ' )\\  )\\ )                 \n| _ \((_) |(_|_)) _((_)) ((_)_(_/(                 \n|  _/ _ \\ / // -_) '  \() _ \\ ' \\))                \n|_|*\\__)/_\\)\\___|_|_|_|\\___/(||_|                 \n ` )  /(( /( (       (  (    )\\ )    (  (          \n  ( )(_))\()))(   (  )\\))(  (()/( (  )\\))(   (     \n (_(_()|(_)\(()\\  )\((_)()\\  ((_)))\((_)()\\  )\\ )  \n |_   _| |(_)((_)((_)(()((_) _| |((_)(()((_)_(_/(  \n   | | | ' \\| '_/ _ \\ V  V / _` / _ \\ V  V / ' \\)) \n   |_| |_||_|_| \\___/\\_/\\_/\\__,_\\___/\\_/\\_/|_||_|  " << endl;
            cout << "                                            " << VERSIONNUMBER << endl;
            break;
        case 2:
            cout << " ,---.   .---.  ,-. .-.,---.           .---.  .-. .-.\n | .-.\\ / .-. ) | |/ / | .-'  |\\    /|/ .-. ) |  \\| |\n | |-' )| | |(_)| | /  | `-.  |(\\  / || | |(_)|   | |\n | |--' | | | | | | \\  | .-'  (_)\\/  || | | | | |\\  |\n | |    \\ `-' / | |) \\ |  `--.| \\  / |\\ `-' / | | |)|\n /(      )---'  |((_)-'/( __.'| |\\/| | )---'  /(  (_)\n(__)    (_)     (_)   (__)    '-'  '-'(_)    (__)\n   _______ .-. .-.,---.    .---.  .-.  .-. ,'|\"\\    .---.  .-.  .-..-. .-.\n  |__   __|| | | || .-.\\  / .-. ) | |/\\| | | |\\ \\  / .-. ) | |/\\| ||  \\| |\n    )| |   | `-' || `-'/  | | |(_)| /  \\ | | | \\ \\ | | |(_)| /  \\ ||   | |\n   (_) |   | .-. ||   (   | | | | |  /\\  | | |  \\ \\| | | | |  /\\  || |\\  |\n     | |   | | |)|| |\\ \\  \\ `-' / |(/  \\ | /(|`-' /\\ `-' / |(/  \\ || | |)|\n     `-'   /(  (_)|_| \\)\\  )---'  (_)   \\|(__)`--'  )---'  (_)   \\|/(  (_)\n          (__)        (__)(_)                      (_)            (__)" << endl;
            cout << "                                                                    " << VERSIONNUMBER << endl;
            break;
        case 3:
            cout << " ___     _\n| _ \\___| |_____ _ __  ___ _ _\n|  _/ _ \\ / / -_) '  \\/ _ \\ ' \\\n|_| \\___/_\\_\\___|_|_|_\\___/_||_| _\n   |_   _| |_  _ _ _____ __ ____| |_____ __ ___ _\n     | | | ' \\| '_/ _ \\ V  V / _` / _ \\ V  V / ' \\\n     |_| |_||_|_| \\___/\\_/\\_/\\__,_\\___/\\_/\\_/|_||_|" << endl;
            cout << "                                             " << VERSIONNUMBER << endl;
            break;
        default:
            cout << "O***0***O***0***O***0" << endl << "* Pokemon Throwdown * " << VERSIONNUMBER << endl << "0***O***0***O***0***O" << endl;
            break;
    }
}

// Game Construction /////////////////////////////////////////////////////////

Game::Game()
{
    m_settings = new Settings;
}

Game::~Game()
{
    delete m_settings;
}