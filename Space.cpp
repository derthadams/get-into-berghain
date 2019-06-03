//
// Created by Derth Adams on 2019-06-03.
//

#include "Space.hpp"

Space::Space(std::string name) : name(name)
{
}

Space::~Space()
{
    for (int i = 0; i < 4; i++)
    {
        if (neighbors[i])
        {
            delete neighbors[i];
            neighbors[i] = nullptr;
        }
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