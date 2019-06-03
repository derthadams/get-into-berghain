/******************************************************************************
**  Program name:  dbl_to_string.cpp
**  Author:        Derth Adams
**  Date:          April 28, 2019
**  Description:   Implementation file for dbl_to_string
*******************************************************************************/
#include <iomanip>
#include <sstream>
#include "dbl_to_string.hpp"

/******************************************************************************
**  Function name:  dbl_to_string
**  Description:    Takes in a double value and returns its string
**                  representation, with a fixed decimal point and one
**                  decimal place of precision.
*******************************************************************************/

std::string dbl_to_string(double value)
{
    std::string output;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << value;
    output = stream.str();
    stream.clear();
    stream.str("");
    return output;
}