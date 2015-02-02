//
//  Menu.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Menu__
#define __PokemonThrowdown__Menu__

#include <vector>
#include <string>
#include <functional> // std::function
#include "Presentable.h"

#define string std::string
#define vector std::vector
#define function std::function

//
// Menu
// Represents a table-based menu displaying a banner up top and a number
// of options represented by numbers that the user can select.
//
class Menu : public Presentable
{
public:
    Menu(string title, vector<string> options, function<void(int)> callback, bool backButtonEnabled = DefaultBackButtonEnabled, int paginationLimit = DefaultPaginationLimit);
    
    string getTitle() const;
    
    vector<string> getOptions() const;
    
    function<void(int)> getCallback() const;
    
    bool getBackButtonEnabled() const;
    
    int getPaginationLimit() const;
    
    void executeCallback(int argument);
    
    static const bool DefaultBackButtonEnabled = false;
    static const int DefaultPaginationLimit = 10;
    
    static const int BackValue = -1;
    static const int NextChoice = -2;
    static const int PrevChoice = -3;
    static const int EndChoice = -4;
    static const int BeginChoice = -5;
    static const int JumpFChoice = -6;
    static const int JumpBChoice = -7;
    static const int NoChoice = -8;
    
private:
    string title;
    vector<string> options;
    function<void(int)> callback;
    bool backButtonEnabled;
    int paginationLimit;
};

#undef function 
#undef vector 
#undef string

#endif /* defined(__PokemonThrowdown__Menu__) */
