//
//  Settings.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 8/23/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "Settings.h"
#include "utilities.h"
#include "constants.h"
#include "strings.h"
#include "trainerdata.h"
#include "pokedata.h"
#include "movedata.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

// Error utility functions

static bool serror()
{
    cerr << "Settings file is invalid!" << endl;
    return false;
}

static bool ioerror()
{
    cerr << "There was an error opening the settings file!" << " "
    << "Settings will not be saved\nbetween program runs." << endl
    << "Run with '-d' option to disable save files." << endl;
    return false;
}

// Helper Functions //////////////////////////////////////////////////////////

static bool testOpenWrite(const string filename)
{
    ofstream settingso;
    
    settingso.open(filename.c_str());
    if (!settingso.is_open())
        return false;
    
    settingso << SETTINGSTAG << endl;
    
    settingso.close();
    return true;
}

// Auxiliary Functions

void chosePokemonInfo(int index)
{
    cout << pokelib[index].name << endl
    << "ID: #" << pokelib[index].ID << endl
    << "Type: " << typeStrings[pokelib[index].type1];
    if (pokelib[index].type2 != NoType)
        cout << "/" << typeStrings[pokelib[index].type2];
    cout << endl
    << "Base Stats:" << endl;
    for (int i = 0; i < NUMSTATS; i++)
        cout << statFullStrings[i] << ": " << pokelib[index].stats[i] << endl;
    cout << "Gender: ";
    if (pokelib[index].gender == NoGender)
        cout << "Any";
    else
        cout << genderStrings[pokelib[index].gender];
    cout << endl
    << "Abilities: ";
    for (int i = 0; i < 3; i++)
    {
        if (i == 0 || pokelib[index].ability[i] != PNoAbility)
        {
            if (i > 0)
                cout << ", ";
            cout << abilityStrings[pokelib[index].ability[i]];
        }
    }
    cout << endl;
    if (pokelib[index].description != "")
        cout << pokelib[index].description << endl;
}

void choseMoveInfo(int index)
{
    cout << "Type: " << typeStrings[movelib[index].type]
    << " Damage: ";
    if (movelib[index].damage == -1)
        cout << "-";
    else
        cout << movelib[index].damage;
    cout << " Accuracy: ";
    if (movelib[index].accuracy == -1)
        cout << "-";
    else
        cout << movelib[index].accuracy;
    cout << " PP: " << movelib[index].PP;
    if (movelib[index].moveType == Status)
        cout << " Move: ";
    else
        cout << " Attack: ";
    cout << moveTypeStrings[movelib[index].moveType] << endl;
    
    if (movelib[index].description != "")
        cout << movelib[index].description << endl;
}

bool chosePokemon(int index, bool confirm)
{
    int ysize = (confirm) ? 1 : 0, csize = 1, choice = -1, prog = 0;
    string yopts[1] = { "Confirm" };
    string copts[1] = { "Info" };
    
    for (;;)
    {
        cout << "You chose " << pokelib[index].name << ":" << endl;
        choice = selectorGadget(copts, csize, prog, csize+ysize, true, NULL, 0, yopts, ysize);
        
        if (choice == BACK)
            return false;
        if (choice == ysize-1) // Confirm
            break;
        else if (choice == ysize) // Info
            chosePokemonInfo(index);
    }
    
    return true;
}

bool choseMove(int index, bool confirm)
{
    int ysize = confirm ? 1: 0, choice = -1, prog = 0;
    string yopts[1] = { "Confirm" };
    
    for (;;)
    {
        cout << "You chose " << movelib[index].name << ":" << endl;
        choseMoveInfo(index);
        choice = selectorGadget(yopts, ysize, prog);
        
        if (choice == BACK)
            return false;
        else if (choice == ysize-1)
            break;
    }
    
    return true;
}

void Settings::defaultTrainer(int whichTrainer)
{
    getTrainer(whichTrainer)->male = true;
    getTrainer(whichTrainer)->name = "Lann";
    getTrainer(whichTrainer)->title = JUGGLER;
    getTrainer(whichTrainer)->reward = 200;
    
    getTrainer(whichTrainer)->numPokemon = 1;
}

void Settings::defaultPokemon(int whichTrainer, int whichPokemon)
{
    getPokemon(whichTrainer, whichPokemon)->index = DF;
    getPokemon(whichTrainer, whichPokemon)->nickname = "Rocky";
    getPokemon(whichTrainer, whichPokemon)->nature = static_cast<Nature>(randInt(1, NUMNATURES-1));
    for (int i = 0; i < NUMSTATS; i++)
    {
        getPokemon(whichTrainer, whichPokemon)->IVs[i] = -1;
        getPokemon(whichTrainer, whichPokemon)->EVs[i] = -1;
    }
    getPokemon(whichTrainer, whichPokemon)->item = HNoItem;
    getPokemon(whichTrainer, whichPokemon)->level = 100;
    getPokemon(whichTrainer, whichPokemon)->gender = (pokelib[DF].gender == NoGender) ? static_cast<Gender>(randInt(0, 1)) : pokelib[DF].gender;
    getPokemon(whichTrainer, whichPokemon)->currentAbility = 0;
    
    getPokemon(whichTrainer, whichPokemon)->moveIDs[0] = 148;
    for (int i = 1; i < MAXMOVES; i++)
        getPokemon(whichTrainer, whichPokemon)->moveIDs[i] = -1;
}

bool Settings::pokeMoveChoice(int choice, int whichTrainer, int whichPokemon, bool moves, int whichMove)
{
    int prog = 0;
    
    switch (choice) // Browse, Search, Random
    {
        default: // case 0
        {
            string* popts;
            if (moves)
                popts = new string[MAXNUMMOVES];
            else
                popts = new string[MAXNUMPOKEMON];
            
            for (int i = 1; i < (moves ? MAXNUMMOVES : MAXNUMPOKEMON); i++)
            {
                ostringstream tmp;
                tmp << (moves ? movelib[i].name : pokelib[i].name) << " (#" << (moves ? movelib[i].ID : pokelib[i].ID) << ")";
                popts[i-1] = tmp.str();
            }
            
            for (;;)
            {
                choice = selectorGadget(popts, (moves ? MAXNUMMOVES : MAXNUMPOKEMON)-1, prog, 10);
                if (choice != BACK)
                {
                    if (moves ? choseMove(choice+1) : chosePokemon(choice+1))
                    {
                        if (moves)
                            getPokemon(whichTrainer, whichPokemon)->moveIDs[whichMove] = choice+1;
                        else
                        {
                            getPokemon(whichTrainer, whichPokemon)->index = choice+1;
                            if (pokelib[getPokemon(whichTrainer, whichPokemon)->index].gender == NoGender
                                && getPokemon(whichTrainer, whichPokemon)->gender == Genderless)
                                getPokemon(whichTrainer, whichPokemon)->gender = NoGender;
                        }
                    }
                    else
                        continue;
                    break;
                }
                else
                {
                    delete[] popts;
                    return false;
                }
            }
            delete[] popts;
        }
            break;
        case 1:
        {
            vector<int> matches;
            string buffer;
        re_search___:
            cout << "Enter search term (type \":q\" to cancel search):" << endl;
            getline(cin, buffer);
            
            if (buffer == ":q")
                return false;
            
            for (int i = 1; i < (moves ? MAXNUMMOVES : MAXNUMPOKEMON); i++)
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
                goto re_search___;
            }
            
            string* matchStrings = new string[matches.size()];
            
            for (int i = 0; i < matches.size(); i++)
            {
                ostringstream tmp;
                tmp << (moves ? movelib[matches[i]].name : pokelib[matches[i]].name) << " (#" << (moves ? movelib[matches[i]].ID : pokelib[matches[i]].ID) << ")";
                matchStrings[i] = tmp.str();
            }
            
            for (;;)
            {
                choice = selectorGadget(matchStrings, static_cast<int>(matches.size()), prog, 10);
                if (choice != BACK)
                {
                    if (moves ? choseMove(matches[choice]) : chosePokemon(matches[choice]))
                    {
                        if (moves)
                            getPokemon(whichTrainer, whichPokemon)->moveIDs[whichMove] = matches[choice];
                        else
                            getPokemon(whichTrainer, whichPokemon)->index = matches[choice];
                    }
                    else
                        continue;
                    break;
                }
                else
                {
                    delete[] matchStrings;
                    matches.clear();
                    goto re_search___;
                }
            }
            
            delete[] matchStrings;
        }
            break;
        case 2:
        {
            int random = randInt(1, (moves ? MAXNUMMOVES : MAXNUMPOKEMON));
            if (moves ? choseMove(random) : chosePokemon(random))
            {
                if (moves)
                    getPokemon(whichTrainer, whichPokemon)->moveIDs[whichMove] = random;
                else
                    getPokemon(whichTrainer, whichPokemon)->index = random;
            }
            else
                return false;
        }
            break;
    }
    
    return true;
}

bool Settings::customizePokemon(int whichTrainer, int whichPokemon)
{
    int choice = -1, prog = 0;
    string opts[12], pokeName;
    
    for (;;)
    {
        prog = 0;
        
        if (getPokemon(whichTrainer, whichPokemon)->nickname == "")
            pokeName = pokelib[getPokemon(whichTrainer, whichPokemon)->index].name;
        else
            pokeName = getPokemon(whichTrainer, whichPokemon)->nickname;
        
        cout << getTrainer(whichTrainer)->title << " " << getTrainer(whichTrainer)->name << "'s ";
        cout << pokeName << ":" << endl;
        
        {
            ostringstream tmp;
            tmp << "Species: " << pokelib[getPokemon(whichTrainer, whichPokemon)->index].name;
            opts[0] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Nickname: ";
            if (getPokemon(whichTrainer, whichPokemon)->nickname == "")
                tmp << "(None)";
            else
                tmp << getPokemon(whichTrainer, whichPokemon)->nickname;
            opts[1] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Nature: " << natureStrings[getPokemon(whichTrainer, whichPokemon)->nature];
            opts[2] = tmp.str();
        }
        
        opts[3] = "Individual Values (IVs)";
        opts[4] = "Effort Values (EVs)";
        
        {
            ostringstream tmp;
            tmp << "Item: " << itemStrings[getPokemon(whichTrainer, whichPokemon)->item];
            opts[5] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Level: " << getPokemon(whichTrainer, whichPokemon)->level;
            opts[6] = tmp.str();
        }
        
        opts[7] = "Moves";
        
        {
            ostringstream tmp;
            tmp << "Gender: ";
            if (pokelib[getPokemon(whichTrainer, whichPokemon)->index].gender != NoGender)
                tmp << genderStrings[pokelib[getPokemon(whichTrainer, whichPokemon)->index].gender];
            else
                tmp << genderStrings[getPokemon(whichTrainer, whichPokemon)->gender];
            opts[8] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Ability: " << abilityStrings[pokelib[getPokemon(whichTrainer, whichPokemon)->index].ability[getPokemon(whichTrainer, whichPokemon)->currentAbility]];
            opts[9] = tmp.str();
        }
        
        opts[10] = "Info";
        
        opts[11] = "Delete";
        
        choice = selectorGadget(opts, 12, prog, 12);
        
        if (choice == BACK)
            return false;
        
        switch (choice)
        {
            case 0:
            {
                for (;;)
                {
                    cout << "Choose a Pokemon:" << endl;
                    string sopts[3] = { "Browse", "Search", "Random" };
                    choice = selectorGadget(sopts, 3, prog);
                    if (choice != BACK)
                        if (!pokeMoveChoice(choice, whichTrainer, whichPokemon))
                            continue;
                    break;
                }
            }
                break;
            case 1:
            {
                string buffer;
                cout << "Enter a nickname (type \":q\" to cancel, empty nickname for no nickname):" << endl;
                getline(cin, buffer);
                if (buffer != ":q")
                    getPokemon(whichTrainer, whichPokemon)->nickname = buffer;
            }
                break;
            case 2:
            {
                string aopts[NUMNATURES];
                for (int i = 0; i < NUMNATURES; i++)
                    aopts[i] = natureStrings[i];
                choice = selectorGadget(aopts, NUMNATURES, prog);
                if (choice != BACK)
                    getPokemon(whichTrainer, whichPokemon)->nature = static_cast<Nature>(choice);
            }
                break;
            case 3:
            case 4:
            {
                bool thisIVs = (choice == 3);
                string vopts[NUMSTATS+3];
                
                for (;;)
                {
                    cout << (thisIVs ? "Individual Values:" : "Effort Values:") << endl;
                    for (int i = 0; i < NUMSTATS; i++)
                    {
                        ostringstream tmp;
                        tmp << statFullStrings[i] << ": ";
                        if (thisIVs)
                        {
                            if (getPokemon(whichTrainer, whichPokemon)->IVs[i] < 0)
                                tmp << "(Don't Care)";
                            else
                                tmp << getPokemon(whichTrainer, whichPokemon)->IVs[i];
                        }
                        else
                        {
                            if (getPokemon(whichTrainer, whichPokemon)->EVs[i] < 0)
                                tmp << "(Don't Care)";
                            else
                                tmp << getPokemon(whichTrainer, whichPokemon)->EVs[i];
                        }
                        vopts[i] = tmp.str();
                    }
                    vopts[NUMSTATS] = (thisIVs ? "Max All" : "Spread Evenly");
                    vopts[NUMSTATS+1] = "Zero All";
                    vopts[NUMSTATS+2] = "Don't Care";
                    choice = selectorGadget(vopts, NUMSTATS+3, prog);
                    if (choice != BACK)
                    {
                        switch (choice)
                        {
                            case NUMSTATS:
                                for (int i = 0; i < NUMSTATS; i++)
                                {
                                    if (thisIVs)
                                        getPokemon(whichTrainer, whichPokemon)->IVs[i] = 31;
                                    else
                                        getPokemon(whichTrainer, whichPokemon)->EVs[i] = 85;
                                }
                                break;
                            case NUMSTATS+1:
                                for (int i = 0; i < NUMSTATS; i++)
                                {
                                    if (thisIVs)
                                        getPokemon(whichTrainer, whichPokemon)->IVs[i] = 0;
                                    else
                                        getPokemon(whichTrainer, whichPokemon)->EVs[i] = 0;
                                }
                                break;
                            case NUMSTATS+2:
                                for (int i = 0; i < NUMSTATS; i++)
                                {
                                    if (thisIVs)
                                        getPokemon(whichTrainer, whichPokemon)->IVs[i] = -1;
                                    else
                                        getPokemon(whichTrainer, whichPokemon)->EVs[i] = -1;
                                }
                                break;
                            default:
                            {
                                int totalVsAll = thisIVs ? 186 : 510, totalVsEach = thisIVs ? 31 : 255, totalVs = 0;
                                cout << "Enter new " << statFullStrings[choice] << (thisIVs ? " IVs" : " EVs") << " (type \":q\" to cancel change):" << endl;
                            new_vs___:
                                ostringstream tmp;
                                tmp << (thisIVs ? "IVs" : "EVs") << " must be integers between 0 and " << (thisIVs ? "31" : "255") << "!";
                                int amount = numericalGadget(0, totalVsEach, tmp.str());
                                if (amount >= 0)
                                {
                                    for (int i = 0; i < NUMSTATS; i++)
                                    {
                                        if (thisIVs)
                                        {
                                            if (getPokemon(whichTrainer, whichPokemon)->IVs[i] < 0)
                                                getPokemon(whichTrainer, whichPokemon)->IVs[i] = 31;
                                        }
                                        else
                                        {
                                            if (getPokemon(whichTrainer, whichPokemon)->EVs[i] < 0)
                                                getPokemon(whichTrainer, whichPokemon)->EVs[i] = 0;
                                        }
                                    }
                                    
                                    totalVs = 0;
                                    for (int i = 0; i < NUMSTATS; i++)
                                    {
                                        if (i == choice)
                                            totalVs += amount;
                                        else
                                            totalVs += thisIVs ? getPokemon(whichTrainer, whichPokemon)->IVs[i] : getPokemon(whichTrainer, whichPokemon)->EVs[i];
                                    }
                                    if (totalVs > totalVsAll)
                                    {
                                        cout << "The maximum EVs allowed on any Pokemon is 510." << endl;
                                        goto new_vs___;
                                    }
                                    else
                                    {
                                        if (thisIVs)
                                            getPokemon(whichTrainer, whichPokemon)->IVs[choice] = amount;
                                        else
                                            getPokemon(whichTrainer, whichPokemon)->EVs[choice] = amount;
                                    }
                                }
                            }
                                break;
                        }
                    }
                    else
                        break;
                }
            }
                break;
            case 5:
            {
                string iopts[NUMITEMS];
                for (int i = 0; i < NUMITEMS; i++)
                    iopts[i] = itemStrings[i];
                choice = selectorGadget(iopts, NUMITEMS, prog);
                if (choice != BACK)
                    getPokemon(whichTrainer, whichPokemon)->item = static_cast<HoldItem>(choice);
            }
                break;
            case 6:
            {
                cout << "Enter new level number (type \":q\" to cancel change):" << endl;
                int newLevel = numericalGadget(1, 100, "Level must be an integer between 1 and 100!");
                if (newLevel > 0)
                    getPokemon(whichTrainer, whichPokemon)->level = newLevel;
            }
                break;
            case 7:
            {
                int numCustomMoves = 0;
                string* mopts;
                int esize = 1;
                string eopts[1] = { "Add Move" };
                for (int i = 0; i < MAXMOVES; i++)
                    if (getPokemon(whichTrainer, whichPokemon)->moveIDs[i] >= 0)
                        numCustomMoves++;
            re_move___:
                cout << getTrainer(whichTrainer)->title << " " << getTrainer(whichTrainer)->name << "'s " << pokeName << "'s Moves:" << endl;
                mopts = new string[numCustomMoves];
                if (numCustomMoves == 4)
                    esize = 0;
                else
                    esize = 1;
                for (int i = 0; i < numCustomMoves; i++)
                    mopts[i] = movelib[getPokemon(whichTrainer, whichPokemon)->moveIDs[i]].name;
                choice = selectorGadget(mopts, numCustomMoves, prog, 4, true, eopts, esize);
                int whichMove = choice;
                if (choice != BACK)
                {
                    if (choice == numCustomMoves)
                        getPokemon(whichTrainer, whichPokemon)->moveIDs[numCustomMoves++] = 165;
                    cout << movelib[getPokemon(whichTrainer, whichPokemon)->moveIDs[whichMove]].name << ":" << endl;
                    choseMoveInfo(getPokemon(whichTrainer, whichPokemon)->moveIDs[whichMove]);
                    string lopts[2] = { "Change", "Delete" };
                    choice = selectorGadget(lopts, 2, prog);
                    
                    if (choice != BACK)
                    {
                        if (choice == 0)
                            for (;;)
                            {
                                cout << "Choose a Move:" << endl;
                                string sopts[3] = { "Browse", "Search", "Random" };
                                choice = selectorGadget(sopts, 3, prog);
                                if (choice != BACK)
                                    if (!pokeMoveChoice(choice, whichTrainer, whichPokemon, true, whichMove))
                                        continue;
                                delete[] mopts;
                                goto re_move___;
                            }
                        else // choice == 1
                        {
                            if (numCustomMoves == 1)
                            {
                                cout << "A Pokemon must have at least one move!" << endl;
                                confirmGadget();
                                delete[] mopts;
                                goto re_move___;
                            }
                            
                            for (int i = whichMove; i < MAXMOVES-1; i++)
                                getPokemon(whichTrainer, whichPokemon)->moveIDs[i] = getPokemon(whichTrainer, whichPokemon)->moveIDs[i+1];
                            getPokemon(whichTrainer, whichPokemon)->moveIDs[MAXMOVES-1] = -1;
                            numCustomMoves--;
                            delete[] mopts;
                            goto re_move___;
                        }
                    }
                    else
                    {
                        delete[] mopts;
                        goto re_move___;
                    }
                }
                delete[] mopts;
            }
                break;
            case 8:
                if (pokelib[getPokemon(whichTrainer, whichPokemon)->index].gender != Genderless)
                    getPokemon(whichTrainer, whichPokemon)->gender = static_cast<Gender>((getPokemon(whichTrainer, whichPokemon)->gender + 1) % 3);
                break;
            case 9:
                getPokemon(whichTrainer, whichPokemon)->currentAbility = (getPokemon(whichTrainer, whichPokemon)->currentAbility + 1) % 3;
                break;
            case 10:
                chosePokemonInfo(getPokemon(whichTrainer, whichPokemon)->index);
                confirmGadget();
                break;
            case 11:
            {
                if (getNumCustomPokemon(whichTrainer) == 1)
                {
                    cout << "You only have one Pokemon left!" << endl;
                    confirmGadget();
                }
                else
                {
                    cout << "Are you sure you want to delete this Pokemon? This cannot be undone." << endl;
                    string copts[2] = { "Yes", "No" };
                    choice = selectorGadget(copts, 2, prog, 2, false);
                    if (choice == 0)
                    {
                        for (int i = whichPokemon; i < getNumCustomPokemon(whichTrainer)-1; i++)
                            setPokemon(*getPokemon(whichTrainer, i+1), whichTrainer, i);
                        defaultPokemon(whichTrainer, getTrainer(whichTrainer)->numPokemon-1);
                        decNumCustomPokemon(whichTrainer);
                        return true;
                    }
                }
            }
                break;
            default:
                break;
        }
    }
    
    return true;
}

bool Settings::customPokemon(int whichTrainer)
{
    int choice = -1, sizeo = 1, prog = 0, csize = getNumCustomPokemon(whichTrainer), esize = 1;
    string opts[1], endOpts[1], cPokemon[MAXPOKEMON];
    
    for (;;)
    {
        prog = 0;
        csize = getNumCustomPokemon(whichTrainer);
        
        cout << getTrainer(whichTrainer)->title << " " << getTrainer(whichTrainer)->name << "'s ";
        cout << "Pokemon:" << endl;
        
        for (int i = 0; i < csize; i++)
        {
            ostringstream tmp;
            if (getPokemon(whichTrainer, i)->nickname == "")
                tmp << pokelib[getPokemon(whichTrainer, i)->index].name;
            else
                tmp << getPokemon(whichTrainer, i)->nickname << " (" << pokelib[getPokemon(whichTrainer, i)->index].name << ")";
            cPokemon[i] = tmp.str();
        }
        
        opts[0] = "Add Pokemon";
        endOpts[0] = "Export Team";
        
        if (csize == MAXPOKEMON)
            sizeo = 0;
        else
            sizeo = 1;
        
        choice = selectorGadget(opts, sizeo, prog, sizeo+csize+esize, true, NULL, 0, cPokemon, csize, endOpts, esize);
        
        if (choice == BACK)
            return false;
        
        if (choice < csize)
            customizePokemon(whichTrainer, choice);
        else if (choice == csize && sizeo == 1)
        {
            customizePokemon(whichTrainer, getNumCustomPokemon(whichTrainer));
            incNumCustomPokemon(whichTrainer);
        }
        else if (choice == csize + sizeo + esize - 1)
        {
            cout << "Do you want to export this team to a text file for future reference?" << endl;
            string yopts[2] = { "Yes", "No" };
            choice = selectorGadget(yopts, 2, prog, 2, false);
            
            if (choice == 0)
            {
                ostringstream tmp;
                string fileName;
                tmp << EXPORTFILENAME << getNumExports() << ".txt";
                fileName = tmp.str();
                
                cout << "Exporting team to './" << fileName << "'..." << endl;
                if (exportTeam(whichTrainer))
                    cout << "Success! Please check './" << fileName << "' to verify your results." << endl;
                else
                    cout << "Oops! The export failed. The program may not have permission to save to this\ndirectory." << endl;
                confirmGadget();
            }
        }
        else
            return false;
    }
    
    return false;
}

bool Settings::customizeTrainer(int whichTrainer)
{
    int choice = -1, prog;
    string opts[6], buffer;
    
    for (;;)
    {
        prog = 0;
        
        cout << getTrainer(whichTrainer)->title << " " << getTrainer(whichTrainer)->name << ":" << endl;
        
        {
            ostringstream tmp;
            tmp << "Name: " << getTrainer(whichTrainer)->name;
            opts[0] = tmp.str();
        }
        {
            ostringstream tmp;
            tmp << "Title: " << getTrainer(whichTrainer)->title;
            opts[1] = tmp.str();
        }
        {
            ostringstream tmp;
            tmp << "Gender: " << genderStrings[!getTrainer(whichTrainer)->male];
            opts[2] = tmp.str();
        }
        {
            ostringstream tmp;
            tmp << "Prize Money: " << getTrainer(whichTrainer)->reward;
            opts[3] = tmp.str();
        }
        opts[4] = "Pokemon";
        opts[5] = "Delete";
        
        choice = selectorGadget(opts, 6, prog);
        
        switch (choice)
        {
            case 0:
                cout << "Enter new name (type \":q\" to cancel name change):" << endl;
                getline(cin, buffer);
                if (buffer != ":q")
                    getTrainer(whichTrainer)->name = buffer;
                break;
            case 1:
            {
                cout << "Choose title:" << endl;
                string topts[NUMTITLES];
                for (int i = 0; i < NUMTITLES; i++)
                    topts[i] = titleArray[i];
                choice = selectorGadget(topts, NUMTITLES, prog, 10);
                if (choice != BACK)
                    getTrainer(whichTrainer)->title = titleArray[choice];
            }
                break;
            case 2:
                getTrainer(whichTrainer)->male = !getTrainer(whichTrainer)->male;
                break;
            case 3:
            {
                cout << "Enter new prize amount (type \":q\" to cancel change):" << endl;
                int amount = numericalGadget(0, 999999, "Prize money must be an integer between 0 and 999999!");
                if (amount >= 0)
                    getTrainer(whichTrainer)->reward = amount;
            }
                break;
            case 4:
                customPokemon(whichTrainer);
                break;
            case 5:
            {
                if (getNumCustomTrainers() == 1)
                {
                    cout << "You need at least one Trainer preset to have a battle!" << endl;
                    confirmGadget();
                }
                else
                {
                    cout << "Are you sure you want to delete this Trainer? This cannot be undone." << endl;
                    string copts[2] = { "Yes", "No" };
                    choice = selectorGadget(copts, 2, prog, 2, false);
                    if (choice == 0)
                    {
                        for (int i = whichTrainer; i < MAXCTRAINERS-1; i++)
                        {
                            setTrainer(*getTrainer(i+1), i);
                            for (int j = 0; j < MAXPOKEMON; j++)
                                setPokemon(*getPokemon(i+1, j), i, j);
                        }
                        defaultTrainer(getNumCustomTrainers()-1);
                        decNumCustomTrainers();
                        return true;
                    }
                }
            }
                break;
            default:
                return false;
        }
    }
    
    return true;
}

bool Settings::exportTeam(int whichTrainer)
{
    ofstream teamExport;
    string fileName;
    
    {
        ostringstream tmp;
        tmp << EXPORTFILENAME << getNumExports() << ".txt";
        fileName = tmp.str();
    }
    
    teamExport.open(fileName.c_str());
    
    if (teamExport.is_open())
        // Export text file with Pokemon properties for future reference
    {
        for (int i = 0; i < getNumCustomPokemon(whichTrainer); i++)
        {
            // Name (Nickname) @ Hold Item
            if (getPokemon(whichTrainer, i)->nickname != "")
                teamExport << getPokemon(whichTrainer, i)->nickname << " (" << pokelib[getPokemon(whichTrainer, i)->index].name << ")";
            else
                teamExport << pokelib[getPokemon(whichTrainer, i)->index].name;
            if (getPokemon(whichTrainer, i)->item != HNoItem)
                teamExport << " @ " << itemStrings[getPokemon(whichTrainer, i)->item];
            teamExport << endl;
            
            // Ability: Something
            if (pokelib[getPokemon(whichTrainer, i)->index].ability[getPokemon(whichTrainer, i)->currentAbility] != PNoAbility)
                teamExport << "Ability: " << abilityStrings[pokelib[getPokemon(whichTrainer, i)->index].ability[getPokemon(whichTrainer, i)->currentAbility]] << endl;
            
            // EVs: 252 Stuff / 4 OtherStuff / 252 SomeOtherStuff
            bool anyEVs = false;
            for (int n = 0; n < NUMSTATS; n++)
                if (getPokemon(whichTrainer, i)->EVs[n] > 0)
                    anyEVs = true;
            if (anyEVs)
            {
                teamExport << "EVs: ";
                int lastStat = 0;
                for (int n = 0; n < NUMSTATS; n++)
                    if (getPokemon(whichTrainer, i)->EVs[n] > 0)
                        lastStat = n;
                for (int n = 0; n < NUMSTATS; n++)
                    if (getPokemon(whichTrainer, i)->EVs[n] > 0)
                    {
                        teamExport << getPokemon(whichTrainer, i)->EVs[n] << " " << statStrings[n];
                        if (n < lastStat)
                            teamExport << " / ";
                    }
                teamExport << endl;
            }
            
            // Some Nature
            if (getPokemon(whichTrainer, i)->nature != NoNature)
                teamExport << natureStrings[getPokemon(whichTrainer, i)->nature] << " Nature" << endl;
            
            // IVs: 30 Something / 30 SomethingElse
            bool anyIVs = false;
            for (int n = 0; n < NUMSTATS; n++)
                if (getPokemon(whichTrainer, i)->IVs[n] > 0 && getPokemon(whichTrainer, i)->IVs[n] < 31)
                    anyIVs = true;
            if (anyIVs)
            {
                teamExport << "IVs: ";
                int lastStat = 0;
                for (int n = 0; n < NUMSTATS; n++)
                    if (getPokemon(whichTrainer, i)->IVs[n] > 0 && getPokemon(whichTrainer, i)->IVs[n] < 31)
                        lastStat = n;
                for (int n = 0; n < NUMSTATS; n++)
                    if (getPokemon(whichTrainer, i)->IVs[n] > 0 && getPokemon(whichTrainer, i)->IVs[n] < 31)
                    {
                        teamExport << getPokemon(whichTrainer, i)->IVs[n] << " " << statStrings[n];
                        if (n < lastStat)
                            teamExport << " / ";
                    }
                teamExport << endl;
            }
            
            // - Move1
            // - Move2
            // - Move3
            // - Move4
            int numMoves = 0;
            for (int n = 0; n < MAXMOVES; n++)
                if (getPokemon(whichTrainer, i)->moveIDs[n] >= 0)
                    numMoves++;
            for (int n = 0; n < numMoves; n++)
                teamExport << "- " << movelib[getPokemon(whichTrainer, i)->moveIDs[n]].name << endl;
            
            teamExport << endl;
        }
        
        teamExport.close();
    }
    else
        return false;
        
    incNumExports();
    return true;
}

// Settings //////////////////////////////////////////////////////////////////

bool Settings::load()
{
    defaultSettings();
    
    cout << endl;
    
    if (!savingEnabled)
        return true;
    
    cout << "Looking for settings file..." << endl;
    
    string buffer;
    ifstream settings;
    
    settings.open(SETTINGSFILENAME.c_str());
    
    if (!settings.is_open()) // no settings file
    {
        cout << "Settings file not found, now attempting to create one." << endl
        << "Creating './" << SETTINGSFILENAME << "'..." << endl;
        
        if (!testOpenWrite(SETTINGSFILENAME))
            return ioerror();
        else
        {
            save();
            cout << "Success!" << endl
            << "Game settings will be saved in './" << SETTINGSFILENAME << "'." << endl
            << "Run with '-d' option to disable save files." << endl;
            return true;
        }
    }
    
    cout << "Settings file './" << SETTINGSFILENAME << "' found!" << endl;
    
    if (!getline(settings, buffer)) // empty file
        if (!testOpenWrite(SETTINGSFILENAME))
            return ioerror();
    
    cout << "Loading from previous save file";
    
    if (buffer != SETTINGSTAG)
        return serror();
    if (!getline(settings, buffer))
        return serror();
    if (buffer.length() != 1 || !isdigit(buffer[0]))
        return serror();
    
    int inputWeather = stringToNumber(buffer);
    if (inputWeather < 0 || inputWeather >= NUMWEATHERS)
        cout << "Invalid weather ID in settings file." << endl;
    setWeatherID(static_cast<Weather>(buffer[0] - '0'));
    cout << ".";
    
    getline(settings, buffer);
    setLocationID(stringToNumber(buffer));
    cout << ".";
    
    getline(settings, buffer);
    int inputMusic = stringToNumber(buffer);
    if (inputMusic < 0 || inputMusic >= NUMTRACKS)
        cout << "Invalid music ID in settings file." << endl;
    setMusicID(inputMusic);
    cout << ".";
    
    getline(settings, buffer);
    setVolumeLevel(stringToNumber(buffer));
    cout << ".";
    
    getline(settings, buffer);
    setSoundEffects(stringToNumber(buffer));
    cout << ".";
    
    getline(settings, buffer);
    int inputMute = stringToNumber(buffer);
    if (inputMute < 0 || inputMute >= 2)
        cout << "Invalid mute setting in settings file." << endl;
    setMuteVolume(stringToNumber(buffer));
    cout << ".";
    
    getline(settings, buffer);
    setAnimations(stringToNumber(buffer));
    cout << ".";
    
    getline(settings, buffer);
    setNumExports(stringToNumber(buffer));
    cout << ".";
    
    getline(settings, buffer);
    setNumCustomTrainers(stringToNumber(buffer));
    cout << ".";
    
    for (int i = 0; i < getNumCustomTrainers(); i++)
    {
        getline(settings, buffer);
        setNumCustomPokemon(stringToNumber(buffer), i);
    }
    cout << ".";
    
    for (int j = 0; j < getNumCustomTrainers(); j++)
    {
        getline(settings, buffer);
        getTrainer(j)->name = buffer;
        getline(settings, buffer);
        getTrainer(j)->title = buffer;
        getline(settings, buffer);
        getTrainer(j)->male = stringToNumber(buffer);
        getline(settings, buffer);
        getTrainer(j)->reward = stringToNumber(buffer);
        
        getline(settings, buffer);
        getTrainer(j)->numPokemon = stringToNumber(buffer);
        
        for (int i = 0; i < getNumCustomPokemon(j); i++)
        {
            getline(settings, buffer);
            getPokemon(j, i)->index = stringToNumber(buffer);
            getline(settings, buffer);
            getPokemon(j, i)->nickname = buffer;
            getline(settings, buffer);
            getPokemon(j, i)->nature = static_cast<Nature>(stringToNumber(buffer));
            getline(settings, buffer);
            getPokemon(j, i)->level = stringToNumber(buffer);
            getline(settings, buffer);
            getPokemon(j, i)->gender = static_cast<Gender>(stringToNumber(buffer));
            getline(settings, buffer);
            getPokemon(j, i)->currentAbility = stringToNumber(buffer);
            
            for (int k = 0; k < NUMSTATS; k++)
            {
                getline(settings, buffer);
                getPokemon(j, i)->IVs[k] = stringToNumber(buffer);
            }
            for (int k = 0; k < NUMSTATS; k++)
            {
                getline(settings, buffer);
                getPokemon(j, i)->EVs[k] = stringToNumber(buffer);
            }
            for (int k = 0; k < MAXMOVES; k++)
            {
                getline(settings, buffer);
                getPokemon(j, i)->moveIDs[k] = stringToNumber(buffer);
            }
        }
        
        cout << ".";
    }
    
    cout << endl;
    
    cout << "Run with '-d' option to disable save files." << endl;
    
    settings.close();
    return true;
}

bool Settings::configure()
{
    int choice = -1, prog = 0;
    const int numSettings = 8;
    string opts[numSettings];
    
    for (;;)
    {
        cout << "Settings:" << endl;
        
        opts[0] = "Trainers";
        
        opts[1] = "Battle Settings";
        
        {
            ostringstream tmp;
            tmp << "Weather: " << weatherStrings[getWeatherID()];
            opts[2] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Location: " << locationStrings[getLocationID()];
            opts[3] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Music: " << musicTracksStrings[getMusicID()];
            opts[4] = tmp.str();
        }
        
        opts[5] = "Volume";
        
        {
            ostringstream tmp;
            tmp << "Animations: " << switchStringsB[getAnimations()] << " (Locked)";
            opts[6] = tmp.str();
        }
        
        opts[7] = "Reset All";
        
        choice = selectorGadget(opts, numSettings, prog);
        
        switch (choice)
        {
            case 0:
                configureTrainers();
                break;
            case 1:
            {
                bool rerun = true;
                const int rsize = 3;
                string ropts[rsize];
                
                while (rerun)
                {
                    cout << "Battle Settings:" << endl;
                    
                    {
                        ostringstream tmp;
                        tmp << "Battle Type: " << battleTypeStrings[getBattleType()] << " (Locked)";
                        ropts[0] = tmp.str();
                    }
                    
                    {
                        ostringstream tmp;
                        tmp << "Battle Rules: " << battleRuleStrings[getBattleRules()] << " (Locked)";
                        ropts[1] = tmp.str();
                    }
                    
                    {
                        ostringstream tmp;
                        tmp << "Battle Level: " << battleLevelStrings[getBattleLevel()] << " (Locked)";
                        ropts[2] = tmp.str();
                    }
                    
                    switch (selectorGadget(ropts, rsize, prog))
                    {
                        case 0:
                        case 1:
                        case 2:
                            break;
                        default:
                            rerun = false;
                            break;
                    }
                }
            }
                break;
            case 2:
                incWeatherID();
                break;
            case 3:
                incLocationID();
                break;
            case 4:
                incMusicID();
                break;
            case 5:
            {
                bool rerun = true;
                const int vsize = 3;
                string vopts[vsize];
                
                while (rerun)
                {
                    cout << "Volume:" << endl;
                    
                    {
                        ostringstream tmp;
                        tmp << "Volume Level: " << getVolumeLevel();
                        vopts[0] = tmp.str();
                    }
                    
                    {
                        ostringstream tmp;
                        tmp << "Sound Effects: " << switchStringsB[getSoundEffects()];
                        vopts[1] = tmp.str();
                    }
                    
                    {
                        ostringstream tmp;
                        tmp << "Mute: " << switchStringsB[getMuteVolume()] << " (Locked)";
                        vopts[2] = tmp.str();
                    }
                    
                    switch (selectorGadget(vopts, vsize, prog))
                    {
                        case 0:
                        {
                            cout << "Enter volume level (0-100, type \":q\" to cancel change):" << endl;
                            int tmpVL = numericalGadget(0, 100, "Volume must be an integer between 0 and 100!");
                            if (tmpVL >= 0)
                                setVolumeLevel(tmpVL);
                        }
                            break;
                        case 1:
                            switchSoundEffects();
                            break;
                        case 2:
                            break;
                        default:
                            rerun = false;
                            break;
                    }
                }
            }
                break;
            case 6:
                break;
            case 7:
            {
                cout << "Are you sure you want to reset settings to default values? All data,\nincluding Custom Trainers and Pokemon, will be reset." << endl;
                string yopts[2] = { "Yes", "No" };
                choice = selectorGadget(yopts, 2, prog, 2, false);
                if (choice == 0)
                {
                    cout << "Resetting..." << endl;
                    defaultSettings();
                    cout << endl;
                }
            }
                break;
            default:
                if (savingEnabled)
                {
                    cout << "Saving..." << endl;
                    
                    if (save())
                        cout << "Settings saved in './" << SETTINGSFILENAME << "'!" << endl;
                    else
                    {
                        cerr << "Could not save settings!" << endl;
                        return false;
                    }
                }
                return true;
        }
    }
}

bool Settings::configureTrainers()
{
    int choice = -1, sizeo = 1, prog = 0;
    string opts[1], cTrainers[MAXCTRAINERS];
    
    for (;;)
    {
        cout << "Trainers:" << endl;
        
        for (int i = 0; i < getNumCustomTrainers(); i++)
        {
            ostringstream tmp;
            tmp << getTrainer(i)->title << " " << getTrainer(i)->name;
            cTrainers[i] = tmp.str();
        }
        
        opts[0] = "Create Trainer";
        
        if (getNumCustomTrainers() == MAXCTRAINERS)
            sizeo = 0;
        else
            sizeo = 1;
        
        choice = selectorGadget(opts, sizeo, prog, sizeo+getNumCustomTrainers(), true, NULL, 0, cTrainers, getNumCustomTrainers());
        
        if (choice == BACK)
            return false;
        
        if (choice < getNumCustomTrainers())
            customizeTrainer(choice);
        else if (choice == getNumCustomTrainers())
        {
            defaultTrainer(getNumCustomTrainers()+1);
            customizeTrainer(getNumCustomTrainers());
            incNumCustomTrainers();
        }
    }
    
    return true;
}

bool Settings::save()
{
    ofstream settings;
    
    settings.open(SETTINGSFILENAME.c_str());
    
    if (settings.is_open())
    {
        settings << SETTINGSTAG << endl
        << getWeatherID() << endl
        << getLocationID() << endl
        << getMusicID() << endl
        << getVolumeLevel() << endl
        << getSoundEffects() << endl
        << getMuteVolume() << endl
        << getAnimations() << endl
        << getNumExports() << endl;
        
        settings << getNumCustomTrainers() << endl;
        for (int i = 0; i < getNumCustomTrainers(); i++)
            settings << getNumCustomPokemon(i) << endl;
        
        for (int j = 0; j < getNumCustomTrainers(); j++)
        {
            settings << getTrainer(j)->name << endl
            << getTrainer(j)->title << endl
            << getTrainer(j)->male << endl
            << getTrainer(j)->reward << endl;
            
            settings << getTrainer(j)->numPokemon << endl;
            
            for (int i = 0; i < getNumCustomPokemon(j); i++)
            {
                settings << getPokemon(j, i)->index << endl
                << getPokemon(j, i)->nickname << endl
                << getPokemon(j, i)->nature << endl
                << getPokemon(j, i)->level << endl
                << getPokemon(j, i)->gender << endl
                << getPokemon(j, i)->currentAbility << endl;
                
                for (int k = 0; k < NUMSTATS; k++)
                    settings << getPokemon(j, i)->IVs[k] << endl;
                for (int k = 0; k < NUMSTATS; k++)
                    settings << getPokemon(j, i)->EVs[k] << endl;
                for (int k = 0; k < MAXMOVES; k++)
                    settings << getPokemon(j, i)->moveIDs[k] << endl;
            }
        }
    }
    else
        return false;
    
    settings.close();
    return true;
}

void Settings::defaultSettings()
{
    setBattleType(SingleBattle);
    setBattleRules(NoRestrictions);
    setBattleLevel(BLAny);
    setWeatherID(RandomWeather);
    setLocationID(Coliseum);
    setMusicID(BWTrainer);
    setVolumeLevel(MAXVOLUMELEVEL);
    setSoundEffects(true);
    setMuteVolume(true);
    setAnimations(false);
    
    setNumCustomTrainers(NUMTRAINERS);
    
    cout << "Initializing variables";
    
    for (int i = 0; i < NUMTRAINERS && i < MAXCTRAINERS; i++)
    {
        setTrainer(trainerlib[i], i);
        for (int j = 0; j < MAXPOKEMON; j++)
            if (j < getNumCustomPokemon(i))
                setPokemon(pokedynamiclib[i][j], i, j);
        
        cout << ".";
    }
    
    for (int i = NUMTRAINERS; i < MAXCTRAINERS; i++)
    {
        defaultTrainer(i);
        for (int j = 0; j < MAXPOKEMON; j++)
            defaultPokemon(i, j);
        
        cout << ".";
    }
    
    zeroNumExports();
}

//

int Settings::getBattleType() const
{
    return m_battleType;
}

int Settings::getBattleRules() const
{
    return m_battleRules;
}

int Settings::getBattleLevel() const
{
    return m_battleLevel;
}

int Settings::getWeatherID() const
{
    return m_weatherID;
}

int Settings::getLocationID() const
{
    return m_locationID;
}

int Settings::getMusicID() const
{
    return m_musicID;
}

int Settings::getVolumeLevel() const
{
    return m_volumeLevel;
}

bool Settings::getSoundEffects() const
{
    return m_soundEffects;
}

bool Settings::getMuteVolume() const
{
    return m_muteVolume;
}

bool Settings::getAnimations() const
{
    return m_animations;
}

int Settings::getNumCustomTrainers() const
{
    return m_numCustomTrainers;
}

int Settings::getNumCustomPokemon(int whichTrainer) const
{
    return m_trainerarray[whichTrainer].numPokemon;
}

pokedynamicdata* Settings::getPokemon(int whichTrainer, int whichPokemon)
{
    return &m_pokedynamicarray[whichTrainer][whichPokemon];
}

trainerdata* Settings::getTrainer(int whichTrainer)
{
    return &m_trainerarray[whichTrainer];
}

int Settings::getNumExports() const
{
    return m_numExports;
}

void Settings::setBattleType(int battleType)
{
    m_battleType = battleType;
}

void Settings::setBattleRules(int battleRules)
{
    m_battleRules = battleRules;
}

void Settings::setBattleLevel(int battleLevel)
{
    m_battleLevel = battleLevel;
}

void Settings::setWeatherID(int weatherID)
{
    m_weatherID = weatherID;
}

void Settings::setLocationID(int locationID)
{
    m_locationID = locationID;
}

void Settings::setMusicID(int musicID)
{
    m_musicID = musicID;
}

void Settings::setVolumeLevel(int volumeLevel)
{
    m_volumeLevel = volumeLevel;
}

void Settings::setSoundEffects(bool soundEffects)
{
    m_soundEffects = soundEffects;
}

void Settings::setMuteVolume(bool muteVolume)
{
    m_muteVolume = muteVolume;
}

void Settings::setAnimations(bool animations)
{
    m_animations = animations;
}

void Settings::setNumCustomTrainers(int numCustomTrainers)
{
    m_numCustomTrainers = numCustomTrainers;
}

void Settings::setNumCustomPokemon(int numCustomPokemon, int whichTrainer)
{
    m_trainerarray[whichTrainer].numPokemon = numCustomPokemon;
}

void Settings::setPokemon(pokedynamicdata pokemon, int whichTrainer, int whichPokemon)
{
    m_pokedynamicarray[whichTrainer][whichPokemon] = pokemon;
}

void Settings::setTrainer(trainerdata trainer, int whichTrainer)
{
    m_trainerarray[whichTrainer] = trainer;
}

void Settings::setNumExports(int numExports)
{
    m_numExports = numExports;
}

void Settings::incBattleType()
{
    setBattleType((getBattleType()+1) % NUMBATTLETYPES);
}

void Settings::incBattleRules()
{
    setBattleRules((getBattleRules()+1) % NUMBATTLERULES);
}

void Settings::incBattleLevel()
{
    setBattleLevel((getBattleLevel()+1) % NUMBATTLELEVELS);
}

void Settings::incWeatherID()
{
    setWeatherID((getWeatherID()+1) % NUMWEATHERS);
}

void Settings::incLocationID()
{
    setLocationID((getLocationID()+1) % NUMLOCATIONS);
}

void Settings::incMusicID()
{
    setMusicID((getMusicID()+1) % NUMTRACKS);
}

void Settings::maxVolumeLevel()
{
    setVolumeLevel(MAXVOLUMELEVEL);
}

void Settings::minVolumeLevel()
{
    setVolumeLevel(MINVOLUMELEVEL);
}

void Settings::switchSoundEffects()
{
    setSoundEffects(!getSoundEffects());
}

void Settings::switchMuteVolume()
{
    setMuteVolume(!getMuteVolume());
}

void Settings::switchAnimations()
{
    setAnimations(!getAnimations());
}

void Settings::incNumCustomTrainers()
{
    setNumCustomTrainers(getNumCustomTrainers()+1);
}

void Settings::decNumCustomTrainers()
{
    setNumCustomTrainers(getNumCustomTrainers()-1);
}

void Settings::zeroNumCustomTrainers()
{
    setNumCustomTrainers(0);
}

void Settings::incNumCustomPokemon(int whichTrainer)
{
    setNumCustomPokemon(getNumCustomPokemon(whichTrainer)+1, whichTrainer);
}

void Settings::decNumCustomPokemon(int whichTrainer)
{
    setNumCustomPokemon(getNumCustomPokemon(whichTrainer)-1, whichTrainer);
}

void Settings::zeroNumCustomPokemon(int whichTrainer)
{
    setNumCustomPokemon(0, whichTrainer);
}

bool Settings::pushPokemon(pokedynamicdata pokemon, int whichTrainer)
{
    if (getNumCustomPokemon(whichTrainer) >= MAXPOKEMON)
        return false;
    else
    {
        setPokemon(pokemon, whichTrainer, getNumCustomPokemon(whichTrainer));
        incNumCustomPokemon(whichTrainer);
        return true;
    }
}

void Settings::removePokemon(int whichTrainer, int whichPokemon)
{
    for (int i = whichPokemon; i < getNumCustomPokemon(whichTrainer)-1; i++)
        setPokemon(*getPokemon(whichTrainer, i+1), whichTrainer, i);
    
    decNumCustomPokemon(whichTrainer);
}

bool Settings::pushTrainer(trainerdata trainer)
{
    if (getNumCustomTrainers() >= MAXCTRAINERS)
        return false;
    else
    {
        setTrainer(trainer, getNumCustomTrainers());
        incNumCustomTrainers();
        return true;
    }
}

void Settings::removeTrainer(int whichTrainer)
{
    for (int i = whichTrainer; i < getNumCustomTrainers()-1; i++)
        setTrainer(*getTrainer(i+1), i);
    
    decNumCustomTrainers();
}

//

void Settings::incNumExports()
{
    setNumExports(getNumExports()+1);
}

void Settings::zeroNumExports()
{
    setNumExports(0);
}