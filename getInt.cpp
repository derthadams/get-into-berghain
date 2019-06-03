/******************************************************************************
**  Program name:  getInt.cpp
**  Author:        Derth Adams
**  Date:          April 7, 2019
**  Description:   Implementation file for getInt()
*******************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include "getInt.hpp"

/******************************************************************************
** Function name:  getInt(string prompt, string error)
** Description:    Input validation function for integers. Takes in two strings,
**                 a prompt and an error message. Prompts the user, takes in
**                 a string as input, and parses the string to make sure it
**                 represents an integer. If it doesn't, the user is shown the
**                 error message and prompted for a new input. If it does,
**                 the function returns the user input as an integer.
******************************************************************************/

int getInt(std::string prompt, std::string error)
{
    while (true)
    {
        bool isInt = true;     // Flag for whether the input represents an int
        std::string input;     // The string input by the user

        // If the user supplied a prompt, prompt the user and
        // get input as a string
        if (!prompt.empty())
        {
            std::cout << prompt << std::endl;
        }
        getline(std::cin, input);

        // If the user didn't type any characters, set flag to indicate
        // they didn't input an integer
        if (input.empty())
        {
            isInt = false;
        }

        // Check to see if the first character is a minus sign. It if is,
        // skip it.
        int start = 0;
        if (input[start] == '-')
        {
            start++;
        }

        // Check each character of the string to make sure it's a digit
        for (int i = start; i < input.length(); i++)
        {
            if(!isdigit(input[i]))
            {
                isInt = false;
            }
        }

        // If the user input a string representing an integer within the system
        // value range for type int, return it as an integer
        if(isInt)
        {
            int result = 0;
            bool inputValid = false;
            while (!inputValid)
            {
                // Stoi exception handling from
                // https://stackoverflow.com/a/18534114
                try
                {
                    result = std::stoi(input);
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

        // If the input did not represent an integer, display the error
        // message and start the process over
        std::cout << error << std::endl;
    }
}