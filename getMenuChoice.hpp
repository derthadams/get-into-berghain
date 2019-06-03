/******************************************************************************
**  Program name: getMenuChoice.hpp
**  Author:       Derth Adams
**  Date:         April 7, 2019
**  Description:  Menu validation function for integer inputs. Accepts a
**                string for a prompt message and two integers representing the
**                lower and upper bounds of the desired input. If no upper
**                bound is desired then set upper to a value of -1.
******************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

int getMenuChoice(std::string prompt, int lower, int upper);
double getMenuChoice(std::string prompt, double lower, double upper);

#endif //MENU_HPP
