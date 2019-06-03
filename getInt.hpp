/******************************************************************************
**  Program name:  getInt.hpp
**  Author:        Derth Adams
**  Date:          April 7, 2019
**  Description:   Input validation function for integers. Takes in two strings,
**                 a prompt and an error message. Prompts the user, takes in
**                 a string as input, and parses the string to make sure it
**                 represents an integer. If it doesn't, the user is shown the
**                 error message and prompted for a new input. If it does,
**                 the function returns the user input as an integer.
*******************************************************************************/

#ifndef GETINT_HPP
#define GETINT_HPP

int getInt(std::string prompt, std::string error);

#endif //GETINT_HPP
