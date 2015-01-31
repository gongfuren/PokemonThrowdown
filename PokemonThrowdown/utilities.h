//
//  utilities.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/30/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__utilities__
#define __PokemonThrowdown__utilities__

#include <iostream> // std::string
#include <sstream> // std::ostringstream
#include <cstdlib> // exit()
#include <limits> // max

//
// toInt()
// Returns an int representation of a number.
//
template <typename T>
int toInt(T number)
{
    return static_cast<int>(number);
}

//
// toDouble()
// Returns a double representation of a number.
//
template <typename T>
double toDouble(T number)
{
    return static_cast<double>(number);
}

//
// toString()
// Returns a string representation of an item.
//
template <typename T>
std::string toString(T item)
{
    std::ostringstream tmp;
    tmp << item;
    return tmp.str();
}

//
// swap()
// Swap two items.
//
template <typename T>
void swap(T& first, T& second)
{
    T temp = first;
    first = second;
    second = temp;
}

//
// max()
// Return the larger of two items.
//
template <typename T>
T max(T first, T second)
{
    return (first > second) ? first : second;
}

//
// min()
// Return the smaller of two items.
//
template <typename T>
T min(T first, T second)
{
    return (first < second) ? first : second;
}

//
// randInt()
// Get a random integer between 0 and range-1, inclusive.
//
int randInt(int range);

//
// randInt()
// Get a random integer between lowest and highest, inclusive.
//
int randInt(int lowest, int highest);

//
// print()
// Prints to console.
//
template <typename T>
void print(T item)
{
    std::cout << item;
}

//
// println()
// Prints to console, followed by a newline.
//
template <typename T>
void println(T item)
{
    std::cout << item << std::endl;
}

//
// error()
// Prints error to console, then exits.
//
template <typename T>
void error(T message)
{
    std::cerr << message << std::endl;
    exit(EXIT_FAILURE);
}

//
// getNumericalInput()
// A utility function that shields the program from std::cin's horrible
// quirks and pitfalls.
// Prompts user for numerical input. Loops until a valid input between 1
// and numChoices inclusive is given.
//
int getNumericalInput(int numChoices);

//
// getStringInput
// Prompts user for string input.
//
std::string getStringInput();

#endif /* defined(__PokemonThrowdown__utilities__) */
