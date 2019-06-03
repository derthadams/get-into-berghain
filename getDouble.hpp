/******************************************************************************
**  Program name:  getDouble.hpp
**  Author:        Derth Adams
**  Date:          April 15, 2019
**  Description:   Input validation function for double. Takes in two strings,
**                 a prompt and an error message. Prompts the user, takes in
**                 a string as input, and parses the string to make sure it
**                 represents an float. If it doesn't, the user is shown the
**                 error message and prompted for a new input. If it does,
**                 the function returns the user input as an integer.
*******************************************************************************/

#ifndef INC_162_PROJECT2_ZOO_GETFLOAT_HPP
#define INC_162_PROJECT2_ZOO_GETFLOAT_HPP

double getDouble(std::string prompt, std::string error);

#endif //INC_162_PROJECT2_ZOO_GETFLOAT_HPP
