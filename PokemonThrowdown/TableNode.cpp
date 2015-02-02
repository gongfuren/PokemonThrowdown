//
//  TableNode.cpp
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "TableNode.h"
#include "TableCellNode.h"
#include "utilities.h" // min(), toInt(), toString()
#include "Menu.h"
#include <functional>
#include <cmath> // ceil()

using namespace std;

TableNode::TableNode(vector<string> labels, int paginationLimit, bool backButtonEnabled, std::function<void(int)> sendInput, WinNode* parent)
: WinNode(parent)
{
    this->currentPage = 0;
    this->numCellsPerPage = paginationLimit;
    this->backButtonEnabled = backButtonEnabled;
    numCellsTotal = toInt(labels.size());
    
    this->sendInput = sendInput;
    
    for (int i = 0; i < numCellsTotal; i++)
    {
        addChild(new TableCellNode(labels[i], i, this));
    }
    
    addChild(new NextTableCellNode(this));
    addChild(new PrevTableCellNode(this));
    addChild(new BackTableCellNode(this));
}

void TableNode::display()
{
    int input = Menu::NoChoice;
    
    for (;;)
    {
        int menuItemNumber = 0;
        const int OffsetNext = toInt(getNextEnabled());
        const int OffsetPrev = toInt(getPrevEnabled());
        const int OffsetBack = toInt(backButtonEnabled);
        
        for (int i = getCurrentIndex(); i < minimum(getCurrentIndex() + numCellsPerPage, numCellsTotal); i++)
        {
            print(toString(++menuItemNumber) + ": ");
            getChildren()[i]->display();
        }
        
        if (getNextEnabled())
        {
            print(toString(++menuItemNumber) + ": ");
            getChildren()[numCellsTotal]->display();
        }
        
        if (getPrevEnabled())
        {
            print(toString(++menuItemNumber) + ": ");
            getChildren()[numCellsTotal + 1]->display();
        }
        
        if (backButtonEnabled)
        {
            print(toString(++menuItemNumber) + ": ");
            getChildren()[numCellsTotal + 2]->display();
        }
        
        // Grab input
        input = getNumericalInput(getNumChoices() + OffsetBack + OffsetNext + OffsetPrev) - 1;
        
        if (input == getNextChoice())
        {
            currentPage = minimum(toInt(ceil(toDouble(numCellsTotal) / toDouble(numCellsPerPage))), currentPage+1);
        }
        else if (input == getPrevChoice())
        {
            currentPage = maximum(0, currentPage-1);
        }
        else if (input == getBackChoice())
        {
            sendInput(Menu::BackValue);
            break;
        }
        else
        {
            sendInput(input + getCurrentIndex());
            break;
        }
    }
}

int TableNode::getCurrentIndex() const
{
    return currentPage * numCellsPerPage;
}

int TableNode::getNumChoices() const
{
    return minimum(numCellsPerPage, numCellsTotal - getCurrentIndex());
}

bool TableNode::getNextEnabled() const
{
    return getCurrentIndex() + numCellsPerPage < numCellsTotal;
}

bool TableNode::getPrevEnabled() const
{
    return currentPage > 0;
}

int TableNode::getNextChoice() const
{
    if (getNextEnabled())
    {
        return getNumChoices();
    }
    else
    {
        return Menu::NoChoice;
    }
}

int TableNode::getPrevChoice() const
{
    if (getPrevEnabled())
    {
        const int OffsetNext = toInt(getNextEnabled());

        return getNumChoices() + OffsetNext;
    }
    else
    {
        return Menu::NoChoice;
    }
}

int TableNode::getBackChoice() const
{
    if (backButtonEnabled)
    {
        const int OffsetNext = toInt(getNextEnabled());
        const int OffsetPrev = toInt(getPrevEnabled());
        
        return getNumChoices() + OffsetNext + OffsetPrev;
    }
    else
    {
        return Menu::NoChoice;
    }
}