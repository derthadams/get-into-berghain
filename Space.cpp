/******************************************************************************
**  Program name:  Space.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Implementation file for the Space class, which is the
**                 abstract base class representing the spaces the player
**                 interacts with in the "Get Into Berghain" game.
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <utility>
#include "Space.hpp"
#include "Constants.hpp"
#include "AsciiArt.hpp"

/******************************************************************************
** Function name: Space()
** Description:   Constructor for the Space class. Sets member variables to
**                their values.
******************************************************************************/

Space::Space(std::string name, std::string introText,
             std::string altIntroText) : name(std::move(name)),
             introText(std::move(introText)),
             altIntroText(std::move(altIntroText))
{
}

/******************************************************************************
** Function name: ~Space()
** Description:   Destructor for the Space class. If neighbors exist, sets
**                the neighbor pointer referring to the Space to nullptr,
**                then deletes the neighbor.
******************************************************************************/

Space::~Space()
{
    if (neighbors[0])
    {
        neighbors[0]->setSouth(nullptr);
        delete neighbors[0];
        neighbors[0] = nullptr;
    }
    if (neighbors[1])
    {
        neighbors[1]->setWest(nullptr);
        delete neighbors[1];
        neighbors[1] = nullptr;
    }
    if (neighbors[2])
    {
        neighbors[2]->setNorth(nullptr);
        delete neighbors[2];
        neighbors[2] = nullptr;
    }
    if (neighbors[3])
    {
        neighbors[3]->setEast(nullptr);
        delete neighbors[3];
        neighbors[3] = nullptr;
    }
}

// Getter for Space pointer in neighbors representing the Space to the north

Space* Space::getNorth()
{
    return neighbors[0];
}

// Getter for Space pointer in neighbors representing the Space to the east

Space* Space::getEast()
{
    return neighbors[1];
}

// Getter for Space pointer in neighbors representing the Space to the south

Space* Space::getSouth()
{
    return neighbors[2];
}

// Getter for Space pointer in neighbors representing the Space to the west

Space* Space::getWest()
{
    return neighbors[3];
}

// Setter for Space pointer in neighbors representing the Space to the north

void Space::setNorth(Space* north)
{
    neighbors[0] = north;
}

// Setter for Space pointer in neighbors representing the Space to the east

void Space::setEast(Space* east)
{
    neighbors[1] = east;
}

// Setter for Space pointer in neighbors representing the Space to the south

void Space::setSouth(Space* south)
{
    neighbors[2] = south;
}

// Setter for Space pointer in neighbors representing the Space to the west

void Space::setWest(Space* west)
{
    neighbors[3] = west;
}

// Getter for the Space's name

std::string Space::getName()
{
    return name;
}

// Getter for the Space's type

SpaceType Space::getType()
{
    return type;
}

/******************************************************************************
** Function name: logline()
** Description:   Takes in two ints representing the current time and the
**                amount in the player's wallet.
**                Displays a status logline indicating the current time,
**                minutes left until all the stores close, the player's
**                current location, and amount of cash left.
*******************************************************************************/

void Space::logLine(int time, int wallet)
{
    std::cout << DINGBAT << std::left << std::setw(11) << "Time:"
              << std::setw(2) << START_HOUR + (time / 60) << ":";
    if (time % 60 < 10)
    {
        std::cout << "0";
    }
    std::cout << (time % 60);
    if (time >= 0 && time <= TIME_LIMIT)
    {
        std::cout  << " (" << TIME_LIMIT - time
                   << " minutes left)  ";
        if (TIME_LIMIT - time < 100)
        {
            std::cout << " ";
            if (TIME_LIMIT - time < 10)
                std::cout << " ";
        }
        std::cout << BATDING;
    }
    else
    {
        std::cout <<
                  " (Your time is up!)  " << BATDING;
    }
    std::cout << DINGBAT << std::setw(11) << "Place:     "
              << std::setw(26) << getName() << BATDING
              << DINGBAT << std::setw(11) << "Cash left: "
              << std::setw(1) << "\u20AC" << std::setw(25)
              << wallet << BATDING << "\n";

}