//
//  settings.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 8/23/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "settings.h"
#include "utilities.h"
#include "constants.h"
#include "strings.h"
#include "trainerdata.h"
#include "pokedata.h"
#include "movedata.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

static void defaultPokemon(pokedynamicdata& p);
static void defaultTrainer(trainerdata& p);
static bool initSet(const string filename);
static bool saveSettings();
static bool customizeTrainer(int whichTrainer);
static void defaultSettings();
static bool exportTeam(int whichTrainer);

static bool serror()
{
    cerr << "Settings file is invalid!" << endl;
    return false;
}

static bool ioerror()
{
    cerr << "There was an error opening the settings file!" << " "
    << "Settings may not be saved\nbetween program runs." << endl;
    return false;
}

int musicID;
int weatherID;
bool muteVolume;
bool soundEffects;
bool animations;
int locationID;
int volumeLevel;
int numCustomTrainers;
int numCustomPokemon[MAXCTRAINERS];

int numExports;

pokedynamicdata pokedynamicarray[MAXCTRAINERS][MAXPOKEMON];
trainerdata trainerarray[MAXCTRAINERS];

// Settings functions

bool customTrainers()
{
    int choice = -1, sizeo = 1, prog = 0;
    string opts[1], cTrainers[MAXCTRAINERS];
    
    while (1)
    {
        cout << "Trainers:" << endl;
        
        for (int i = 0; i < numCustomTrainers; i++)
        {
            ostringstream tmp;
            tmp << trainerarray[i].title << " " << trainerarray[i].name;
            cTrainers[i] = tmp.str();
        }
        
        opts[0] = "Create Trainer";
        
        if (numCustomTrainers == MAXCTRAINERS)
            sizeo = 0;
        else
            sizeo = 1;
        
        choice = selectorGadget(opts, sizeo, prog, sizeo+numCustomTrainers, true, NULL, 0, cTrainers, numCustomTrainers);
        
        if (choice == BACK)
        {
            cout << "Saving..." << endl;
            if (saveSettings())
                cout << "Settings saved in './" << SETTINGSFILENAME << "'!" << endl;
            else
                cout << "Could not save settings!" << endl;
            return false;
        }
        
        if (choice < numCustomTrainers)
            customizeTrainer(choice);
        else if (choice == numCustomTrainers)
        {
            defaultTrainer(trainerarray[numCustomTrainers+1]);
            customizeTrainer(numCustomTrainers++);
        }
    }
    
    return true;
}

void configureSettings()
{
    int choice = -1, prog = 0;
    const int numSettings = 8;
    string opts[numSettings];
    
    while (1)
    {
        cout << "Settings:" << endl;
        
        {
            ostringstream tmp;
            tmp << "Weather: " << weatherStrings[weatherID];
            opts[0] = tmp.str();
        }
        
        // Location
        
        {
            ostringstream tmp;
            tmp << "Location: " << locationStrings[locationID];
            opts[1] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Music: " << musicTracksStrings[musicID];
            opts[2] = tmp.str();
        }
        
        // Volume
        
        {
            ostringstream tmp;
            tmp << "Volume: " << volumeLevel;
            opts[3] = tmp.str();
        }
        
        // Sound Effects
        
        {
            ostringstream tmp;
            tmp << "Sound Effects: " << switchStringsB[soundEffects];
            opts[4] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Mute: " << switchStringsB[muteVolume];
            opts[5] = tmp.str();
        }
        
        // Animations
        
        {
            ostringstream tmp;
            tmp << "Animations: " << switchStringsB[animations];
            opts[6] = tmp.str();
        }
        
        opts[7] = "Reset All";
        
        choice = selectorGadget(opts, numSettings, prog);
        
        switch (choice)
        {
            case 0:
                weatherID = (weatherID+1) % NUMWEATHERS;
                break;
            case 1:
                locationID = (locationID+1) % NUMLOCATIONS;
                break;
            case 2:
                musicID = (musicID+1) % NUMTRACKS;
                break;
            case 3:
            {
                cout << "Enter volume level (1-100, type \":q\" to cancel change):" << endl;
                int tmpVL = numericalGadget(0, 100, "Volume must be an integer between 0 and 100!");
                if (tmpVL >= 0)
                    volumeLevel = tmpVL;
            }
                break;
            case 4:
                soundEffects = !soundEffects;
                break;
            case 5:
            case 6:
                break;
            case 7:
            {
                cout << "Are you sure you want to reset settings to default values? All data,\nincluding Custom Trainers and Pokemon, will be reset." << endl;
                string yopts[2] = { "Yes", "No" };
                choice = selectorGadget(yopts, 2, prog, 2, false);
                if (choice == 0)
                {
                    cout << "Resetting settings";
                    defaultSettings();
                    cout << endl;
                }
            }
                break;
            default:
                cout << "Saving..." << endl;
                if (saveSettings())
                    cout << "Settings saved in './" << SETTINGSFILENAME << "'!" << endl;
                else
                    cerr << "Could not save settings!" << endl;
                return;
        }
    }
}

static bool saveSettings()
{
    ofstream settings;
    
    settings.open(SETTINGSFILENAME);
    
    if (settings.is_open())
    {
        settings << SETTINGSTAG << endl
        << weatherID << endl
        << locationID << endl
        << musicID << endl
        << volumeLevel << endl
        << soundEffects << endl
        << muteVolume << endl
        << animations << endl
        << numExports << endl;
        
        settings << numCustomTrainers << endl;
        for (int i = 0; i < numCustomTrainers; i++)
            settings << numCustomPokemon[i] << endl;
        
        for (int j = 0; j < numCustomTrainers; j++)
        {
            settings << trainerarray[j].name << endl
            << trainerarray[j].title << endl
            << trainerarray[j].male << endl
            << trainerarray[j].reward << endl;
            
            for (int i = 0; i < MAXPOKEMON; i++)
                settings << trainerarray[j].pokemonIDs[i] << endl;
            
            for (int i = 0; i < numCustomPokemon[j]; i++)
            {
                settings << pokedynamicarray[j][i].index << endl
                << pokedynamicarray[j][i].nickname << endl
                << pokedynamicarray[j][i].nature << endl
                << pokedynamicarray[j][i].level << endl
                << pokedynamicarray[j][i].gender << endl
                << pokedynamicarray[j][i].currentAbility << endl;
                
                for (int k = 0; k < NUMSTATS; k++)
                    settings << pokedynamicarray[j][i].IVs[k] << endl;
                for (int k = 0; k < NUMSTATS; k++)
                    settings << pokedynamicarray[j][i].EVs[k] << endl;
                for (int k = 0; k < MAXMOVES; k++)
                    settings << pokedynamicarray[j][i].moveIDs[k] << endl;
            }
        }
    }
    else
        return false;
    
    settings.close();
    return true;
}

bool loadSettings()
{
    cout << "Loading..." << endl;
    
    cout << "Initializing settings variables";
    
    defaultSettings();
    
    cout << endl;
    
    cout << "Looking for settings file..." << endl;
    
    string buffer;
    ifstream settings;
    
    settings.open(SETTINGSFILENAME);
    
    if (!settings.is_open()) // no settings file
    {
        cout << "Settings file not found, now attempting to create one." << endl
        << "Creating './" << SETTINGSFILENAME << "'..." << endl;
        
        if (!initSet(SETTINGSFILENAME))
            return ioerror();
        else
        {
            saveSettings();
            cout << "Success!" << endl
            << "Game settings will be saved in './" << SETTINGSFILENAME << "'." << endl;
            return true;
        }
    }
    
    cout << "Settings file './" << SETTINGSFILENAME << "' found!" << endl;
    
    if (!getline(settings, buffer)) // empty file
        if (!initSet(SETTINGSFILENAME))
            return ioerror();
    
    cout << "Loading settings";
    
    if (buffer != SETTINGSTAG)
        return serror();
    if (!getline(settings, buffer))
        return serror();
    if (buffer.length() != 1 || !isnumber(buffer[0]))
        return serror();
    
    int inputWeather = stringToNumber(buffer);
    if (inputWeather < 0 || inputWeather >= NUMWEATHERS)
        cout << "Invalid weather ID in settings file." << endl;
    weatherID = static_cast<Weather>(buffer[0] - '0');
    cout << ".";
    
    getline(settings, buffer);
    locationID = stringToNumber(buffer);
    cout << ".";
    
    getline(settings, buffer);
    int inputMusic = stringToNumber(buffer);
    if (inputMusic < 0 || inputMusic >= NUMTRACKS)
        cout << "Invalid music ID in settings file." << endl;
    musicID = inputMusic;
    cout << ".";
    
    getline(settings, buffer);
    volumeLevel = stringToNumber(buffer);
    cout << ".";
    
    getline(settings, buffer);
    soundEffects = stringToNumber(buffer);
    cout << ".";
    
    getline(settings, buffer);
    int inputMute = stringToNumber(buffer);
    if (inputMute < 0 || inputMute >= 2)
        cout << "Invalid mute setting in settings file." << endl;
    muteVolume = stringToNumber(buffer);
    cout << ".";
    
    getline(settings, buffer);
    animations = stringToNumber(buffer);
    cout << ".";
    
    getline(settings, buffer);
    numExports = stringToNumber(buffer);
    cout << ".";
    
    getline(settings, buffer);
    numCustomTrainers = stringToNumber(buffer);
    cout << ".";
    
    for (int i = 0; i < numCustomTrainers; i++)
    {
        getline(settings, buffer);
        numCustomPokemon[i] = stringToNumber(buffer);
    }
    cout << ".";
    
    for (int j = 0; j < numCustomTrainers; j++)
    {
        getline(settings, buffer);
        trainerarray[j].name = buffer;
        getline(settings, buffer);
        trainerarray[j].title = buffer;
        getline(settings, buffer);
        trainerarray[j].male = stringToNumber(buffer);
        getline(settings, buffer);
        trainerarray[j].reward = stringToNumber(buffer);
        
        for (int i = 0; i < MAXPOKEMON; i++)
        {
            getline(settings, buffer);
            trainerarray[j].pokemonIDs[i] = stringToNumber(buffer);
        }
        
        for (int i = 0; i < numCustomPokemon[j]; i++)
        {
            getline(settings, buffer);
            pokedynamicarray[j][i].index = stringToNumber(buffer);
            getline(settings, buffer);
            pokedynamicarray[j][i].nickname = buffer;
            getline(settings, buffer);
            pokedynamicarray[j][i].nature = static_cast<Nature>(stringToNumber(buffer));
            getline(settings, buffer);
            pokedynamicarray[j][i].level = stringToNumber(buffer);
            getline(settings, buffer);
            pokedynamicarray[j][i].gender = static_cast<Gender>(stringToNumber(buffer));
            getline(settings, buffer);
            pokedynamicarray[j][i].currentAbility = stringToNumber(buffer);
            
            for (int k = 0; k < NUMSTATS; k++)
            {
                getline(settings, buffer);
                pokedynamicarray[j][i].IVs[k] = stringToNumber(buffer);
            }
            for (int k = 0; k < NUMSTATS; k++)
            {
                getline(settings, buffer);
                pokedynamicarray[j][i].EVs[k] = stringToNumber(buffer);
            }
            for (int k = 0; k < MAXMOVES; k++)
            {
                getline(settings, buffer);
                pokedynamicarray[j][i].moveIDs[k] = stringToNumber(buffer);
            }
        }
        
        cout << ".";
    }
    
    cout << endl;
    
    cout << "Done!" << endl;
    
    settings.close();
    return true;
}

static bool initSet(const string filename)
{
    ofstream settingso;
    
    settingso.open(filename);
    if (!settingso.is_open())
        return false;
    
    settingso << SETTINGSTAG << endl;
    settingso << (RandomWeather - NoWeather) << endl;
    
    settingso.close();
    return true;
}

static void defaultSettings()
{
    weatherID = RandomWeather;
    locationID = Coliseum;
    musicID = BWTrainer;
    volumeLevel = 100;
    soundEffects = true;
    muteVolume = true;
    animations = false;
    
    numCustomTrainers = NUMTRAINERS;
    
    for (int i = 0; i < NUMTRAINERS && i < MAXCTRAINERS; i++)
    {
        trainerarray[i] = trainerlib[i];
        numCustomPokemon[i] = 0;
        for (int j = 0; j < MAXPOKEMON; j++)
        {
            if (trainerlib[i].pokemonIDs[j] >= 0)
            {
                pokedynamicarray[i][j] = pokedynamiclib[trainerlib[i].pokemonIDs[j]];
                numCustomPokemon[i]++;
            }
            trainerarray[i].pokemonIDs[j] = j;
        }
    }
    
    for (int i = NUMTRAINERS; i < MAXCTRAINERS; i++)
    {
        defaultTrainer(trainerarray[i]);
        numCustomPokemon[i] = 1;
        for (int j = 0; j < MAXPOKEMON; j++)
            defaultPokemon(pokedynamicarray[i][j]);
        
        cout << ".";
    }
    
    numExports = 0;
}

// Auxiliary Functions

static bool chosePokemonInfo(int index)
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
    
    return true;
}

static bool choseMoveInfo(int index)
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
    
    return true;
}

bool chosePokemon(int index, bool confirm)
{
    int ysize = (confirm) ? 1 : 0, csize = 1, choice = -1, prog = 0;
    string yopts[1] = { "Confirm" };
    string copts[1] = { "Info" };
    
    while (1)
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
    
    while (1)
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

static void defaultTrainer(trainerdata& t)
{
    t.male = true;
    t.name = "Lann";
    t.title = JUGGLER;
    t.reward = 200;
    
    t.pokemonIDs[0] = 0;
    for (int j = 1; j < MAXPOKEMON; j++)
        t.pokemonIDs[j] = -1;
}

static void defaultPokemon(pokedynamicdata& p)
{
    p.index = DF;
    p.nickname = "Rocky";
    p.nature = static_cast<Nature>(randInt(1, NUMNATURES-1));
    for (int i = 0; i < NUMSTATS; i++)
    {
        p.IVs[i] = -1;
        p.EVs[i] = -1;
    }
    p.item = HNoItem;
    p.level = 100;
    p.gender = (pokelib[DF].gender == NoGender) ? static_cast<Gender>(randInt(0, 1)) : pokelib[DF].gender;
    p.currentAbility = 0;
    
    p.moveIDs[0] = 148;
    for (int i = 1; i < MAXMOVES; i++)
        p.moveIDs[i] = -1;
}

static bool pokeMoveChoice(int choice, int whichTrainer, int whichPokemon, bool moves = false, int whichMove = 0)
{
    int prog = 0;
    
    switch (choice)
    {
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
                
                for (int i = 0; i < candidate.length(); i++)
                    candidate[i] = tolower(candidate[i]);
                for (int i = 0; i < term.length(); i++)
                    term[i] = tolower(term[i]);
                
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
                matchStrings[i] = (moves ? movelib[matches[i]].name : pokelib[matches[i]].name);
            
            while (1)
            {
                choice = selectorGadget(matchStrings, static_cast<int>(matches.size()), prog, 10);
                if (choice != BACK)
                {
                    if (moves ? choseMove(matches[choice]) : chosePokemon(matches[choice]))
                    {
                        if (moves)
                            pokedynamicarray[whichTrainer][whichPokemon].moveIDs[whichMove] = matches[choice];
                        else
                            pokedynamicarray[whichTrainer][whichPokemon].index = matches[choice];
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
                    pokedynamicarray[whichTrainer][whichPokemon].moveIDs[whichMove] = random;
                else
                    pokedynamicarray[whichTrainer][whichPokemon].index = random;
            }
            else
                return false;
        }
            break;
        default:
        {
            string* popts;
            if (moves)
                popts = new string[MAXNUMMOVES];
            else
                popts = new string[MAXNUMPOKEMON];
            
            for (int i = 1; i < (moves ? MAXNUMMOVES : MAXNUMPOKEMON); i++)
                popts[i-1] = (moves ? movelib[i].name : pokelib[i].name);
            while (1)
            {
                choice = selectorGadget(popts, (moves ? MAXNUMMOVES : MAXNUMPOKEMON)-1, prog, 10);
                if (choice != BACK)
                {
                    if (moves ? choseMove(choice+1) : chosePokemon(choice+1))
                    {
                        if (moves)
                            pokedynamicarray[whichTrainer][whichPokemon].moveIDs[whichMove] = choice+1;
                        else
                        {
                            pokedynamicarray[whichTrainer][whichPokemon].index = choice+1;
                            if (pokelib[pokedynamicarray[whichTrainer][whichPokemon].index].gender == NoGender
                                && pokedynamicarray[whichTrainer][whichPokemon].gender == Genderless)
                                pokedynamicarray[whichTrainer][whichPokemon].gender = NoGender;
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
    }
    
    return true;
}

static bool customizePokemon(int whichTrainer, int whichPokemon)
{
    int choice = -1, prog = 0;
    string opts[12], pokeName;
    
    while (1)
    {
        prog = 0;
        
        if (pokedynamicarray[whichTrainer][whichPokemon].nickname == "")
            pokeName = pokelib[pokedynamicarray[whichTrainer][whichPokemon].index].name;
        else
            pokeName = pokedynamicarray[whichTrainer][whichPokemon].nickname;
        
        cout << trainerarray[whichTrainer].title << " " << trainerarray[whichTrainer].name << "'s ";
        cout << pokeName << ":" << endl;
        
        {
            ostringstream tmp;
            tmp << "Species: " << pokelib[pokedynamicarray[whichTrainer][whichPokemon].index].name;
            opts[0] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Nickname: ";
            if (pokedynamicarray[whichTrainer][whichPokemon].nickname == "")
                tmp << "(None)";
            else
                tmp << pokedynamicarray[whichTrainer][whichPokemon].nickname;
            opts[1] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Nature: " << natureStrings[pokedynamicarray[whichTrainer][whichPokemon].nature];
            opts[2] = tmp.str();
        }
        
        opts[3] = "Individual Values (IVs)";
        opts[4] = "Effort Values (EVs)";
        
        {
            ostringstream tmp;
            tmp << "Item: " << itemStrings[pokedynamicarray[whichTrainer][whichPokemon].item];
            opts[5] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Level: " << pokedynamicarray[whichTrainer][whichPokemon].level;
            opts[6] = tmp.str();
        }
        
        opts[7] = "Moves";
        
        {
            ostringstream tmp;
            tmp << "Gender: ";
            if (pokelib[pokedynamicarray[whichTrainer][whichPokemon].index].gender != NoGender)
                tmp << genderStrings[pokelib[pokedynamicarray[whichTrainer][whichPokemon].index].gender];
            else
                tmp << genderStrings[pokedynamicarray[whichTrainer][whichPokemon].gender];
            opts[8] = tmp.str();
        }
        
        {
            ostringstream tmp;
            tmp << "Ability: " << abilityStrings[pokelib[pokedynamicarray[whichTrainer][whichPokemon].index].ability[pokedynamicarray[whichTrainer][whichPokemon].currentAbility]];
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
                while (1)
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
                    pokedynamicarray[whichTrainer][whichPokemon].nickname = buffer;
            }
                break;
            case 2:
            {
                string aopts[NUMNATURES];
                for (int i = 0; i < NUMNATURES; i++)
                    aopts[i] = natureStrings[i];
                choice = selectorGadget(aopts, NUMNATURES, prog);
                if (choice != BACK)
                    pokedynamicarray[whichTrainer][whichPokemon].nature = static_cast<Nature>(choice);
            }
                break;
            case 3:
            case 4:
            {
                bool thisIVs = (choice == 3);
                string vopts[NUMSTATS+3];
                
                while (1)
                {
                    cout << (thisIVs ? "Individual Values:" : "Effort Values:") << endl;
                    for (int i = 0; i < NUMSTATS; i++)
                    {
                        ostringstream tmp;
                        tmp << statFullStrings[i] << ": ";
                        if (thisIVs)
                        {
                            if (pokedynamicarray[whichTrainer][whichPokemon].IVs[i] < 0)
                                tmp << "(Don't Care)";
                            else
                                tmp << pokedynamicarray[whichTrainer][whichPokemon].IVs[i];
                        }
                        else
                            tmp << pokedynamicarray[whichTrainer][whichPokemon].EVs[i];
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
                                        pokedynamicarray[whichTrainer][whichPokemon].IVs[i] = 31;
                                    else
                                        pokedynamicarray[whichTrainer][whichPokemon].EVs[i] = 85;
                                }
                                break;
                            case NUMSTATS+1:
                                for (int i = 0; i < NUMSTATS; i++)
                                {
                                    if (thisIVs)
                                        pokedynamicarray[whichTrainer][whichPokemon].IVs[i] = 0;
                                    else
                                        pokedynamicarray[whichTrainer][whichPokemon].EVs[i] = 0;
                                }
                                break;
                            case NUMSTATS+2:
                                for (int i = 0; i < NUMSTATS; i++)
                                {
                                    if (thisIVs)
                                        pokedynamicarray[whichTrainer][whichPokemon].IVs[i] = -1;
                                    else
                                        pokedynamicarray[whichTrainer][whichPokemon].EVs[i] = -1;
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
                                            if (pokedynamicarray[whichTrainer][whichPokemon].IVs[i] < 0)
                                                pokedynamicarray[whichTrainer][whichPokemon].IVs[i] = 31;
                                        }
                                        else
                                        {
                                            if (pokedynamicarray[whichTrainer][whichPokemon].EVs[i] < 0)
                                                pokedynamicarray[whichTrainer][whichPokemon].EVs[i] = 0;
                                        }
                                    }
                                    
                                    totalVs = 0;
                                    for (int i = 0; i < NUMSTATS; i++)
                                    {
                                        if (i == choice)
                                            totalVs += amount;
                                        else
                                            totalVs += thisIVs ? pokedynamicarray[whichTrainer][whichPokemon].IVs[i] : pokedynamicarray[whichTrainer][whichPokemon].EVs[i];
                                    }
                                    if (totalVs > totalVsAll)
                                    {
                                        cout << "The maximum EVs allowed on any Pokemon is 510." << endl;
                                        goto new_vs___;
                                    }
                                    else
                                    {
                                        if (thisIVs)
                                            pokedynamicarray[whichTrainer][whichPokemon].IVs[choice] = amount;
                                        else
                                            pokedynamicarray[whichTrainer][whichPokemon].EVs[choice] = amount;
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
                    pokedynamicarray[whichTrainer][whichPokemon].item = static_cast<HoldItem>(choice);
            }
                break;
            case 6:
            {
                cout << "Enter new level number (type \":q\" to cancel change):" << endl;
                int newLevel = numericalGadget(1, 100, "Level must be an integer between 1 and 100.");
                if (newLevel > 0)
                    pokedynamicarray[whichTrainer][whichPokemon].level = newLevel;
            }
                break;
            case 7:
            {
                int numCustomMoves = 0;
                string* mopts;
                int esize = 1;
                string eopts[1] = { "Add Move" };
                for (int i = 0; i < MAXMOVES; i++)
                    if (pokedynamicarray[whichTrainer][whichPokemon].moveIDs[i] >= 0)
                        numCustomMoves++;
            re_move___:
                cout << trainerarray[whichTrainer].title << " " << trainerarray[whichTrainer].name << "'s " << pokeName << "'s Moves:" << endl;
                mopts = new string[numCustomMoves];
                if (numCustomMoves == 4)
                    esize = 0;
                else
                    esize = 1;
                for (int i = 0; i < numCustomMoves; i++)
                    mopts[i] = movelib[pokedynamicarray[whichTrainer][whichPokemon].moveIDs[i]].name;
                choice = selectorGadget(mopts, numCustomMoves, prog, 4, true, eopts, esize);
                int whichMove = choice;
                if (choice != BACK)
                {
                    if (choice == numCustomMoves)
                        pokedynamicarray[whichTrainer][whichPokemon].moveIDs[numCustomMoves++] = 165;
                    cout << movelib[pokedynamicarray[whichTrainer][whichPokemon].moveIDs[whichMove]].name << ":" << endl;
                    choseMoveInfo(pokedynamicarray[whichTrainer][whichPokemon].moveIDs[whichMove]);
                    string lopts[2] = { "Change", "Delete" };
                    choice = selectorGadget(lopts, 2, prog);
                    
                    if (choice != BACK)
                    {
                        if (choice == 0)
                            while (1)
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
                                pokedynamicarray[whichTrainer][whichPokemon].moveIDs[i] = pokedynamicarray[whichTrainer][whichPokemon].moveIDs[i+1];
                            pokedynamicarray[whichTrainer][whichPokemon].moveIDs[MAXMOVES-1] = -1;
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
                if (pokelib[pokedynamicarray[whichTrainer][whichPokemon].index].gender != Genderless)
                    pokedynamicarray[whichTrainer][whichPokemon].gender = static_cast<Gender>((pokedynamicarray[whichTrainer][whichPokemon].gender + 1) % 3);
                break;
            case 9:
                pokedynamicarray[whichTrainer][whichPokemon].currentAbility = (pokedynamicarray[whichTrainer][whichPokemon].currentAbility + 1) % 3;
                break;
            case 10:
                chosePokemonInfo(pokedynamicarray[whichTrainer][whichPokemon].index);
                confirmGadget();
                break;
            case 11:
            {
                if (numCustomPokemon[whichTrainer] == 1)
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
                        for (int i = whichPokemon; i < numCustomPokemon[whichTrainer]-1; i++)
                            pokedynamicarray[whichTrainer][i] = pokedynamicarray[whichTrainer][i+1];
                        defaultPokemon(pokedynamicarray[whichTrainer][numCustomPokemon[whichTrainer]-1]);
                        trainerarray[whichTrainer].pokemonIDs[numCustomPokemon[whichTrainer]-1] = -1;
                        numCustomPokemon[whichTrainer]--;
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

static bool customPokemon(int whichTrainer)
{
    int choice = -1, sizeo = 1, prog = 0, csize = numCustomPokemon[whichTrainer], esize = 1;
    string opts[1], endOpts[1], cPokemon[MAXPOKEMON];
    
    while (1)
    {
        prog = 0;
        csize = numCustomPokemon[whichTrainer];
        
        cout << trainerarray[whichTrainer].title << " " << trainerarray[whichTrainer].name << "'s ";
        cout << "Pokemon:" << endl;
        
        for (int i = 0; i < csize; i++)
        {
            ostringstream tmp;
            if (pokedynamicarray[whichTrainer][i].nickname == "")
                tmp << pokelib[pokedynamicarray[whichTrainer][i].index].name;
            else
                tmp << pokedynamicarray[whichTrainer][i].nickname << " (" << pokelib[pokedynamicarray[whichTrainer][i].index].name << ")";
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
            trainerarray[whichTrainer].pokemonIDs[numCustomPokemon[whichTrainer]] = numCustomPokemon[whichTrainer];
            customizePokemon(whichTrainer, numCustomPokemon[whichTrainer]++);
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
                tmp << EXPORTFILENAME << numExports << ".txt";
                fileName = tmp.str();
                
                cout << "Exporting team to './" << fileName << "'..." << endl;
                if (exportTeam(whichTrainer))
                    cout << "Success! Please check './" << fileName << "' to verify your results." << endl;
                else
                    cout << "Oops! The export failed. I may not have permission to save to this\ndirectory." << endl;
                confirmGadget();
            }
        }
        else
            return false;
    }
    
    return false;
}

static bool customizeTrainer(int whichTrainer)
{
    int choice = -1, prog;
    string opts[6], buffer;
    
    while (1)
    {
        prog = 0;
        
        cout << trainerarray[whichTrainer].title << " " << trainerarray[whichTrainer].name << ":" << endl;
        
        {
            ostringstream tmp;
            tmp << "Name: " << trainerarray[whichTrainer].name;
            opts[0] = tmp.str();
        }
        {
            ostringstream tmp;
            tmp << "Title: " << trainerarray[whichTrainer].title;
            opts[1] = tmp.str();
        }
        {
            ostringstream tmp;
            tmp << "Gender: " << genderStrings[!trainerarray[whichTrainer].male];
            opts[2] = tmp.str();
        }
        {
            ostringstream tmp;
            tmp << "Prize Money: " << trainerarray[whichTrainer].reward;
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
                    trainerarray[whichTrainer].name = buffer;
                break;
            case 1:
            {
                cout << "Choose title:" << endl;
                string topts[NUMTITLES];
                for (int i = 0; i < NUMTITLES; i++)
                    topts[i] = titleArray[i];
                choice = selectorGadget(topts, NUMTITLES, prog, 10);
                if (choice != BACK)
                    trainerarray[whichTrainer].title = titleArray[choice];
            }
                break;
            case 2:
                trainerarray[whichTrainer].male = !trainerarray[whichTrainer].male;
                break;
            case 3:
            {
                cout << "Enter new prize amount (type \":q\" to cancel change):" << endl;
                int amount = numericalGadget(0, 999999, "Prize money must be an integer between 0 and 999999");
                if (amount >= 0)
                    trainerarray[whichTrainer].reward = amount;
            }
                break;
            case 4:
                customPokemon(whichTrainer);
                break;
            case 5:
            {
                if (numCustomTrainers == 1)
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
                            trainerarray[i] = trainerarray[i+1];
                            numCustomPokemon[i] = numCustomPokemon[i+1];
                            for (int j = 0; j < MAXPOKEMON; j++)
                                pokedynamicarray[i][j] = pokedynamicarray[i+1][j];
                        }
                        defaultTrainer(trainerarray[numCustomTrainers-1]);
                        numCustomPokemon[numCustomTrainers-1] = 1;
                        numCustomTrainers--;
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

static bool exportTeam(int whichTrainer)
{
    ofstream teamExport;
    string fileName;
    ostringstream tmp;
    
    tmp << EXPORTFILENAME << numExports << ".txt";
    fileName = tmp.str();
    
    teamExport.open(fileName);
    
    if (teamExport.is_open())
        // Export text file with Pokemon properties for future reference
    {
        for (int i = 0; i < numCustomPokemon[whichTrainer]; i++)
        {
            // Name (Nickname) @ Hold Item
            if (pokedynamicarray[whichTrainer][i].nickname != "")
                teamExport << pokedynamicarray[whichTrainer][i].nickname << " (" << pokelib[pokedynamicarray[whichTrainer][i].index].name << ")";
            else
                teamExport << pokelib[pokedynamicarray[whichTrainer][i].index].name;
            if (pokedynamicarray[whichTrainer][i].item != HNoItem)
                teamExport << " @ " << itemStrings[pokedynamicarray[whichTrainer][i].item];
            teamExport << endl;
            
            // Ability: Something
            if (pokelib[pokedynamicarray[whichTrainer][i].index].ability[pokedynamicarray[whichTrainer][i].currentAbility] != PNoAbility)
                teamExport << "Ability: " << abilityStrings[pokelib[pokedynamicarray[whichTrainer][i].index].ability[pokedynamicarray[whichTrainer][i].currentAbility]] << endl;
            
            // EVs: 252 Stuff / 4 OtherStuff / 252 SomeOtherStuff
            bool anyEVs = false;
            for (int n = 0; n < NUMSTATS; n++)
                if (pokedynamicarray[whichTrainer][i].EVs[n] > 0)
                    anyEVs = true;
            if (anyEVs)
            {
                teamExport << "EVs: ";
                int lastStat = 0;
                for (int n = 0; n < NUMSTATS; n++)
                    if (pokedynamicarray[whichTrainer][i].EVs[n] > 0)
                        lastStat = n;
                for (int n = 0; n < NUMSTATS; n++)
                    if (pokedynamicarray[whichTrainer][i].EVs[n] > 0)
                    {
                        teamExport << pokedynamicarray[whichTrainer][i].EVs[n] << " " << statStrings[n];
                        if (n < lastStat)
                            teamExport << " / ";
                    }
                teamExport << endl;
            }
            
            // Some Nature
            if (pokedynamicarray[whichTrainer][i].nature != NoNature)
                teamExport << natureStrings[pokedynamicarray[whichTrainer][i].nature] << " Nature" << endl;
            
            // IVs: 30 Something / 30 SomethingElse
            bool anyIVs = false;
            for (int n = 0; n < NUMSTATS; n++)
                if (pokedynamicarray[whichTrainer][i].IVs[n] > 0 && pokedynamicarray[whichTrainer][i].IVs[n] < 31)
                    anyIVs = true;
            if (anyIVs)
            {
                teamExport << "IVs: ";
                int lastStat = 0;
                for (int n = 0; n < NUMSTATS; n++)
                    if (pokedynamicarray[whichTrainer][i].IVs[n] > 0 && pokedynamicarray[whichTrainer][i].IVs[n] < 31)
                        lastStat = n;
                for (int n = 0; n < NUMSTATS; n++)
                    if (pokedynamicarray[whichTrainer][i].IVs[n] > 0 && pokedynamicarray[whichTrainer][i].IVs[n] < 31)
                    {
                        teamExport << pokedynamicarray[whichTrainer][i].IVs[n] << " " << statStrings[n];
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
                if (pokedynamicarray[whichTrainer][i].moveIDs[n] >= 0)
                    numMoves++;
            for (int n = 0; n < numMoves; n++)
                teamExport << "- " << movelib[pokedynamicarray[whichTrainer][i].moveIDs[n]].name << endl;
            
            teamExport << endl;
        }
        
        teamExport.close();
    }
    else
        return false;
        
    numExports++;
    return true;
}