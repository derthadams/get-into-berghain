/******************************************************************************
**  Program name:  getDouble.cpp
**  Author:        Derth Adams
**  Date:          April 15, 2019
**  Description:   Implementation file for getDouble()
*******************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include "getDouble.hpp"

/******************************************************************************
** Function name:  getDouble()
** Description:    Input validation function for double. Takes in two strings,
**                 a prompt and an error message. Prompts the user, takes in
**                 a string as input, and parses the string to make sure it
**                 represents an float. If it doesn't, the user is shown the
**                 error message and prompted for a new input. If it does,
**                 the function returns the user input as an integer.
******************************************************************************/

double getDouble(std::string prompt, std::string error)
{
    while (true)
    {
        bool isDouble = true;  // Flag for whether the input represents a double
        std::string input;     // The string input by the user

        // If the user supplied a prompt, prompt the user and
        // get input as a string
        if (!prompt.empty())
        {
            std::cout << prompt << std::endl;
        }
        getline(std::cin, input);

        // If the user didn't type any characters, set flag to indicate
        // they didn't input a double
        if (input.empty())
        {
            isDouble = false;
        }

        // Check to see if the first character is a minus sign. It if is,
        // skip it.
        int start = 0;
        if (input[start] == '-')
        {
            start++;
        }

        // Check each character of the string to make sure it's a digit or
        // a decimal point
        int decimalCount = 0;
        for (int i = start; i < input.length(); i++)
        {
            if(!isdigit(input[i]) && input[i] != '.')
            {
                isDouble = false;
            }
            if(input[i] == '.')
            {
                decimalCount++;
            }
        }
        if (decimalCount > 1)
        {
            isDouble = false;
        }

        // If the user input a string representing a double within the system
        // value range for type double, return it as a double
        if(isDouble)
        {
            double result = 0.0;
            bool inputValid = false;
            while (!inputValid)
            {
                // Stoi exception handling from
                // https://stackoverflow.com/a/18534114
                try
                {
                    result = std::stod(input);
                    inputValid = true;
                }
                catch (std::out_of_range&)
                {
                    std::cout << "Your number was out of range, try again: "
                              << std::endl;
                    getline(std::cin, input);
                }
                catch (std::invalid_argument&)
                {
                    std::cout << "Invalid input, try again: "
                              << std::endl;
                    getline(std::cin, input);
                }
            }
            return result;
        }

        // If the input did not represent a double, display the error
        // message and start the process over
        std::cout << error << std::endl;
    }
}