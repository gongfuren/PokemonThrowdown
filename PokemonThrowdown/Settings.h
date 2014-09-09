//
//  Settings.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 8/23/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__settings__
#define __PokemonThrowdown__settings__

#include <iostream>
#include "constants.h"
#include "trainerdata.h"
#include "pokedata.h"

// Settings Functions ////////////////////////////////////////////////////////

// chosePokemon()/choseMove()
// Allow user to view summary of Pokemon and moves.
bool chosePokemon(int index, bool confirm = true);
bool choseMove(int index, bool confirm = true);

// chosePokemonInfo()/choseMoveInfo()
// Creates string describing Pokemon and Move info in pokelib and movelib
void choseMoveInfo(int index);
void chosePokemonInfo(int index);

// Settings Variables ////////////////////////////////////////////////////////

// Command Line

extern bool savingEnabled;

// Settings //////////////////////////////////////////////////////////////////

class Settings
{
public:
    // Core functions
    bool configure();
    bool configureTrainers();

    bool load();
    bool save();
    bool exportTeam(int whichTrainer);
    
    void defaultSettings();
    
    // Secondary functions
    void defaultTrainer(int whichTrainer);
    void defaultPokemon(int whichTrainer, int whichPokemon);
    bool customizePokemon(int whichTrainer, int whichPokemon);
    bool customPokemon(int whichTrainer);
    bool customizeTrainer(int whichTrainer);
    bool pokeMoveChoice(int choice, int whichTrainer, int whichPokemon, bool moves = false, int whichMove = 0);
    
    // Accessor (get) functions
    int getBattleType() const;
    int getBattleRules() const;
    int getBattleLevel() const;
    
    int getWeatherID() const;
    int getLocationID() const;
    int getMusicID() const;
    int getVolumeLevel() const;
    bool getSoundEffects() const;
    bool getMuteVolume() const;
    bool getAnimations() const;
    
    int getNumCustomTrainers() const;
    int getNumCustomPokemon(int whichTrainer) const;
    pokedynamicdata* getPokemon(int whichTrainer, int whichPokemon);
    trainerdata* getTrainer(int whichTrainer);
        
    int getNumExports() const;
    
    // Mutator (set) functions
    void setBattleType(int battleType);
    void setBattleRules(int battleRules);
    void setBattleLevel(int battleLevel);
    
    void setWeatherID(int weatherID);
    void setLocationID(int locationID);
    void setMusicID(int musicID);
    void setVolumeLevel(int volumeLevel);
    void setSoundEffects(bool soundEffects);
    void setMuteVolume(bool muteVolume);
    void setAnimations(bool animations);
    
    void setNumCustomTrainers(int numCustomTrainers);
    void setNumCustomPokemon(int numCustomPokemon, int whichTrainer);
    void setPokemon(pokedynamicdata pokemon, int whichTrainer, int whichPokemon);
    void setTrainer(trainerdata trainer, int whichTrainer);
    
    void setNumExports(int numExports);
    
    // Secondary mutator functions
    void incBattleType();
    void incBattleRules();
    void incBattleLevel();
    
    void incWeatherID();
    void incLocationID();
    void incMusicID();
    void maxVolumeLevel();
    void minVolumeLevel();
    void switchSoundEffects();
    void switchMuteVolume();
    void switchAnimations();
    
    void incNumCustomTrainers();
    void decNumCustomTrainers();
    void zeroNumCustomTrainers();
    void incNumCustomPokemon(int whichTrainer);
    void decNumCustomPokemon(int whichTrainer);
    void zeroNumCustomPokemon(int whichTrainer);
    bool pushPokemon(pokedynamicdata pokemon, int whichTrainer);
    void removePokemon(int whichTrainer, int whichPokemon);
    bool pushTrainer(trainerdata trainer);
    void removeTrainer(int whichTrainer);
    
    void incNumExports();
    void zeroNumExports();
    
private:
    // Data members
    int m_battleType;
    int m_battleRules;
    int m_battleLevel;
    
    int m_weatherID;
    int m_locationID;
    int m_musicID;
    int m_volumeLevel;
    int m_soundEffects;
    int m_muteVolume;
    int m_animations;
    
    int m_numCustomTrainers;
    pokedynamicdata m_pokedynamicarray[MAXCTRAINERS][MAXPOKEMON];
    trainerdata m_trainerarray[MAXCTRAINERS];
    
    int m_numExports;
};

// Settings File /////////////////////////////////////////////////////////////

// Line number references

const int NAMETAG = 0;
const int WEATHERTAG = 1;
const int TRAINERSTART = 2;
const int TRAINERENTRYSIZE = 4;
const int POKEENTRYSIZE = 8;
const int TNPENTRY = TRAINERENTRYSIZE + POKEENTRYSIZE * 6;

// String constants

const std::string SETTINGSTAG = "PKTDS04IPC2014___";
const std::string SETTINGSFILENAME = "PKTDSettings.txt";
const std::string EXPORTFILENAME = "PKTDExport";

const std::string VERSIONNUMBER = "v0.5";

#endif /* defined(__PokemonThrowdown__settings__) */
