//
//  utils.cpp
//  pokemongame
//
//  Created by Ian Cordero on 6/6/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

#include "constants.h"
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

// Auxiliary Function Implementations

double typeMultiplier(Type type1, Type type2, Type type3)
{
    if (type3 == NoType)
        return typeArray[type1][type2];
    else
        return typeArray[type1][type2] * typeArray[type1][type3];
}

int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    return lowest + (rand() % (highest - lowest + 1));
}

double natureMultiplier(Nature nature, int stat)
{
    return natureArray[nature][stat];
}

int selectorGadget(string opts[], int sizeo, int& prog,
                   int entriesPerPage, bool back,
                   string specialOpts[], int sizes,
                   string specialBeginOpts[], int sizeb,
                   string specialEndOpts[], int sizee)
{
    int i, j, k, choice, noffs, poffs, nhoffs, phoffs, nloffs, ploffs;
    bool next, prev, nexth, prevh, nextl, prevl, jump, alphaOmega;
    
    nexth = false;
    prevh = false;
    nextl = false;
    prevl = false;
    
    if (prog < 0)
        prog = 0;
    if (prog > sizeo + sizeb + sizee)
        prog = (sizeo + sizee + sizeb)
        - ((sizeo + sizee + sizeb) % entriesPerPage);
    
    if (sizeo + sizee + sizeb > 100)
        jump = true;
    else
        jump = false;
    
    if (sizeo + sizee + sizeb > 20)
        alphaOmega = true;
    else
        alphaOmega = false;
    
    for (i = prog;;)
    {
        prog = i;
        
        noffs = 0;
        poffs = 0;
        nhoffs = 0;
        phoffs = 0;
        nloffs = 0;
        ploffs = 0;
        
        for (j = 0; j < entriesPerPage && i+j < sizeo + sizee + sizeb; j++)
        {
            cout << j+1 << ": ";
            
            if (i+j < sizeb)
                cout << specialBeginOpts[i+j];
            else if (i+j < sizeb + sizeo)
                cout << opts[i+j - sizeb];
            else
                cout << specialEndOpts[i+j - (sizeb + sizeo)];
            
            cout << endl;
        }
        
        for (k = 0; k < sizes; k++)
            cout << j++ + 1 << ": " << specialOpts[k] << endl;
        
        if (i + entriesPerPage < sizeo + sizeb + sizee)
        {
            cout << j++ + 1 << ": " << "(" << "Next" << ")" << " >>" << endl;
            next = true;
        }
        else
            next = false;
        
        if (i > 0)
        {
            cout << j++ + 1 << ": " << "<< " << "(" << "Prev" << ")" << endl;
            prev = true;
            
            noffs++;
        }
        else
            prev = false;
        
        if (jump)
        {
            if (i + 100 < sizeo + sizeb + sizee)
            {
                cout << j++ + 1 << ": " << "(" << "Jump Forward" << ")"
                << " 100>>" << endl;
                nexth = true;
                
                noffs++;
                poffs++;
            }
            else
                nexth = false;
            
            if (i >= 100)
            {
                cout << j++ + 1 << ": " << "<<100 " << "(" << "Jump Back" << ")"
                << endl;
                prevh = true;
                
                noffs++;
                poffs++;
                nhoffs++;
            }
            else
                prevh = false;
        }
        
        if (alphaOmega)
        {
            if (i + entriesPerPage < sizeo + sizeb + sizee)
            {
                cout << j++ + 1 << ": " << "(" << "Skip to End" << ")" << " ->|"
                << endl;
                nextl = true;
                
                noffs++;
                poffs++;
                nhoffs++;
                phoffs++;
            }
            else
                nextl = false;
            
            if (i > 0)
            {
                cout << j++ + 1 << ": " << "|<- " << "(" << "Beginning" << ")"
                << endl;
                prevl = true;
                
                noffs++;
                poffs++;
                nhoffs++;
                phoffs++;
                nloffs++;
            }
            else
                prevl = false;
        }
        
        if (back)
        {
            cout << j++ + 1 << ": " << ".. " << "(" << "Back" << ")" << endl;
            
            noffs++;
            poffs++;
            nhoffs++;
            phoffs++;
            nloffs++;
            ploffs++;
        }
        
        cin >> choice;
        
        if (choice <= 0 || choice > j)
            continue;
        else if (next && choice == j - noffs)
        {
            i += entriesPerPage;
            continue;
        }
        else if (prev && choice == j - poffs)
        {
            i -= entriesPerPage;
            if (i < 0)
                i = 0;
            continue;
        }
        else if (nexth && choice == j - nhoffs)
        {
            i += 100;
            continue;
        }
        else if (prevh && choice == j - phoffs)
        {
            i -= 100;
            if (i < 0)
                i = 0;
            continue;
        }
        else if (nextl && choice == j - nloffs)
        {
            i = (sizeo + sizee + sizeb)
            - ((sizeo + sizee + sizeb) % entriesPerPage);
            continue;
        }
        else if (prevl && choice == j - ploffs)
        {
            i = 0;
            continue;
        }
        else if (back && choice == j)
            return BACK;
        else
            return choice + prog - 1;
    }
}