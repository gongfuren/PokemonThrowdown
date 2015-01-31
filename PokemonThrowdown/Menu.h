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

//
// Menu
// Represents a table-based menu displaying a banner up top and a number
// of options represented by numbers that the user can select.
//
class Menu
{
public:
    Menu(std::string title, std::vector<std::string> options, std::function<void(int)> callback);
    
    std::string getTitle() const;
    
    std::vector<std::string> getOptions() const;
    
    std::function<void(int)> getCallback() const;
    
    void executeCallback(int argument);
    
private:
    std::string title;
    std::vector<std::string> options;
    std::function<void(int)> callback;
};

#endif /* defined(__PokemonThrowdown__Menu__) */
