//
// Created by Derth Adams on 2019-06-03.
//

#include <iostream>
#include "Store.hpp"
#include "getMenuChoice.hpp"

Store::Store(std::string name, std::string introText,
             std::string altIntroText, std::string clerkName,
             std::string clerkDescription) : Space::Space(name, introText,
                     altIntroText), clerkName(clerkName),
                     clerkDescription(clerkDescription)
{
    type = store;
}

Store::~Store()
{
    for (int i = 0; i < inventory.size(); i++)
    {
        delete inventory.at(i);
        inventory.at(i) = nullptr;
    }
}

std::string Store::getClerkName()
{
    return clerkName;
}

std::string Store::getClerkDescription()
{
    return clerkDescription;
}

NextMove Store::scene(int time, int& wallet, Outfit* outfit)
{
    if (visited)
    {
        std::cout << altIntroText;
    }
    else
    {
        std::cout << introText << "\n";
        std::cout << clerkDescription;
    }
    std::cout  << "\n\n";
    visited = true;
    std::cout << "A few items catch your eye:\n\n";
    for (int i = 0; i < inventory.size(); i++)
    {
        std::cout << "\u25AA   " << inventory.at(i)->name<< "\n";
    }
    std::cout << "\n";
    int exitIndex;
    for (int j = 0; j < 4; j++)
    {
        if (neighbors[j])
        {
            exitIndex = j;
        }
    }
    std::cout << "1. Exit store\n";
    int choice = getMenuChoice("", 1, 1);
    return static_cast<NextMove>(exitIndex);
}

void Store::addItem(Item* item)
{
    inventory.push_back(item);
}

bool Store::isOpen(int time)
{
    return (time <= 120);
}