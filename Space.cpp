//
// Created by Derth Adams on 2019-06-03.
//
#include <iostream>
#include <utility>
#include "Space.hpp"
#include "Constants.hpp"

Space::Space(std::string name, std::string introText,
             std::string altIntroText) : name(std::move(name)),
             introText(std::move(introText)),
             altIntroText(std::move(altIntroText))
{
}

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

Space* Space::getNorth()
{
    return neighbors[0];
}

Space* Space::getEast()
{
    return neighbors[1];
}

Space* Space::getSouth()
{
    return neighbors[2];
}

Space* Space::getWest()
{
    return neighbors[3];
}

void Space::setNorth(Space* north)
{
    neighbors[0] = north;
}

void Space::setEast(Space* east)
{
    neighbors[1] = east;
}

void Space::setSouth(Space* south)
{
    neighbors[2] = south;
}

void Space::setWest(Space* west)
{
    neighbors[3] = west;
}

std::string Space::getName()
{
    return name;
}

SpaceType Space::getType()
{
    return type;
}

void Space::logLine(int time, int wallet)
{
    std::cout << SEPARATOR;
    std::cout << "Time:      " << START_HOUR + (time / 60) << ":";
    if (time % 60 < 10)
    {
        std::cout << "0";
    }
    std::cout << (time % 60);
    if (time >= 0 && time <= TIME_LIMIT)
    {
        std::cout  << " (" << TIME_LIMIT - time
                   << " minutes left)\n";
    }
    else
    {
        std::cout <<
                  " (Your time is up)" << "\n";
    }
    std::cout << "Place:     " << getName() << "\n"
              << "Cash left: \u20AC" << wallet << "\n\n";
}

//void Space::addItem(Item*)
//{
//
//}

//bool Space::isOpen(int time)
//{
//    return false;
//}

//void Space::addClerkResponse(std::string const&)
//{
//
//}
//
//void Space::addPascalResponse(std::string const&)
//{
//
//}