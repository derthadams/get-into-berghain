/******************************************************************************
**  Program name:  getString.cpp
**  Author:        Derth Adams
**  Date:          April 28, 2019
**  Description:   Input validation function for strings. Takes a string
**                 representing the prompt and returns the validated string
**                 input by the user.
*******************************************************************************/

#include "getString.hpp"
#include <iostream>

std::string getString(std::string prompt)
{
    std::string input;
    std::cout << prompt << std::endl;
    std::getline(std::cin, input);
    while(input.empty() || input[0] == ' ')
    {
        std::cout << "Invalid input, please try again: ";
        std::getline(std::cin, input);
    }
    return input;
}