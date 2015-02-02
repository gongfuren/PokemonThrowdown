//
//  TableNode.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__TableNode__
#define __PokemonThrowdown__TableNode__

#include "WinNode.h"
#include <vector>
#include <iostream>
#include <functional>

#define override virtual

//
// TableNode
// Represents a scrollable table view of items. When called to display contents, grabs user input
// for a selection of one of its cells.
//
class TableNode : public WinNode
{
public:
    TableNode(std::vector<std::string> labels, int paginationLimit, bool backButtonEnabled, std::function<void(int)> sendInput, WinNode* parent);
    
    override void display();
    
    int getCurrentIndex() const;
    
    int getNumChoices() const;
    
    bool getNextEnabled() const;
    
    bool getPrevEnabled() const;
    
    int getNextChoice() const;
    
    int getPrevChoice() const;
    
    int getBackChoice() const;
        
private:
    int currentPage;
    int numCellsPerPage;
    bool backButtonEnabled;
    int numCellsTotal;
    std::function<void(int)> sendInput;
};

#undef override

#endif /* defined(__PokemonThrowdown__TableNode__) */
