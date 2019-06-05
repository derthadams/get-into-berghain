//
// Created by Derth Adams on 2019-06-03.
//
#include <iostream>
#include "Space.hpp"

Space::Space(std::string name, std::string introText,
             std::string altIntroText) : name(name), introText(introText),
             altIntroText(altIntroText)
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

void Space::addItem(Item*)
{

}

bool Space::isOpen(int time)
{
}