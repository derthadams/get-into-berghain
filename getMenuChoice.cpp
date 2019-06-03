/******************************************************************************
**  Program name: getMenuChoice.cpp
**  Author:       Derth Adams
**  Date:         April 7, 2019
**  Description:  Implementation file for getMenuChoice()
******************************************************************************/

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "getMenuChoice.hpp"
#include "getInt.hpp"
#include "getDouble.hpp"
#include "dbl_to_string.hpp"

/******************************************************************************
** Function name: getMenuChoice (string, int, int)
** Description:   Menu validation function for integer inputs. Accepts a
**                string for a prompt message and two integers representing the
**                lower and upper bounds of the desired input. If no upper
**                bound is desired then set upper to a value of -1.
******************************************************************************/

int getMenuChoice(std::string prompt, int lower, int upper)
{
    int choice = 0;         // User's input
    bool upperBound = true; // Whether or not the validation has an upper bound
    std::string error; // Error message

    // If the validation has no upper bound
    if (upper == -1)
    {
        error = "Invalid entry. Please enter a number "
                            + std::to_string(lower) + " or larger: ";
        upperBound = false;
    }
    // If the validation has an upper bound
    else
    {
        error = "Invalid entry. Please enter a number between " +
                            std::to_string(lower) + " and " +
                            std::to_string(upper) + ": ";
    }

    // Display the prompt and get user input
    std::cout << prompt << std::endl;
    choice = getInt("", error);

    // Validates whether the input is within the desired range
    // and repeats the prompt until the user enters valid input.
    while (true)
    {
        if (upperBound)
        {
            if (choice >= lower && choice <= upper)
            {
                return choice;
            }
            else
            {
                std::cout << error;
                choice = getInt("", error);
            }
        }
        else
        {
            if (choice >= lower)
            {
                return choice;
            }
            else
            {
                std::cout << error;
                choice = getInt("", error);
            }
        }
    }
}

/******************************************************************************
** Function name: getMenuChoice (string, double, double)
** Description:   Menu validation function for double inputs. Accepts a
**                string for a prompt message and two doubles representing the
**                lower and upper bounds of the desired input. If no upper
**                bound is desired then set upper to a value of -1.
******************************************************************************/

double getMenuChoice(std::string prompt, double lower, double upper)
{
    double choice = 0.0;    // User's input
    bool upperBound = true; // Whether or not the validation has an upper bound
    std::string error;      // Error message

    // If the validation has no upper bound
    if (upper == -1)
    {
        error = "Invalid entry. Please enter a number "
                + dbl_to_string(lower) + " or larger: ";
        upperBound = false;
    }
        // If the validation has an upper bound
    else
    {
        error = "Invalid entry. Please enter a number between " +
                dbl_to_string(lower) + " and " + dbl_to_string(upper) + ": ";
    }

    // Display the prompt and get user input
    std::cout << prompt << std::endl;
    choice = getDouble("", error);

    // Validates whether the input is within the desired range
    // and repeats the prompt until the user enters valid input.
    while (true)
    {
        if (upperBound)
        {
            if (choice >= lower && choice <= upper)
            {
                return choice;
            }
            else
            {
                std::cout << error;
                choice = getDouble("", error);
            }
        }
        else
        {
            if (choice >= lower)
            {
                return choice;
            }
            else
            {
                std::cout << error;
                choice = getDouble("", error);
            }
        }
    }
}