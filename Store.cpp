//
// Created by Derth Adams on 2019-06-03.
//

#include <iostream>
#include <iomanip>
#include <utility>
#include "Store.hpp"
#include "getMenuChoice.hpp"

Store::Store(std::string name, std::string introText,
             std::string altIntroText, std::string clerkName,
             std::string clerkDescription) : Space::Space(std::move(name),
                     std::move(introText), std::move(altIntroText)),
                     clerkName(std::move(clerkName)),
                     clerkDescription(std::move(clerkDescription))
{
    type = store;
}

Store::~Store()
{
//    for (int i = 0; i < inventory.size(); i++)
//    {
//        delete inventory.at(i);
//        inventory.at(i) = nullptr;
//    }
    for (Item* item : inventory)
    {
        delete item;
        item = nullptr;
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

int Store::getExitIndex()
{
    for (int j = 0; j < 4; j++)
    {
        if (neighbors[j])
        {
            return j;
        }
    }
    return -1;
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

    std::cout << "A few items catch your eye:\n";
    int categoryIndex = -1;
    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory.at(i)->category != categoryIndex)
        {
            categoryIndex++;
            std::cout << "\n** " << categories[categoryIndex] << " **\n";
        }
        std::cout << i + 1 << ".   " << std::left << std::setw(62)
                  << inventory.at(i)->name << std::setw(5)
                  << "   (\u20AC" << inventory.at(i)->price << ")\n";
    }
    std::cout << "\n";

    int choice = 0;
    while (choice != inventory.size() + 2)
    {
        std::cout << "What would you like to do?\n\n";
        std::cout << "To try on an item, enter the item's number.\n";
        std::cout << inventory.size() + 1
                  << ". Review what you're wearing now\n";
        std::cout << inventory.size() + 2
                  << ". Exit store\n";
        choice = getMenuChoice("", 1, static_cast<int>(inventory.size()) + 2);
        if (choice <= inventory.size())
        {
            // Try on inventory.at(i)
        }
        else if (choice == inventory.size() + 1)
        {
            outfit->areWearing();
        }
    }
    return static_cast<NextMove>(getExitIndex());
}

void Store::addItem(Item* item)
{
    inventory.push_back(item);
}

bool Store::isOpen(int time)
{
    return (time <= 120);
}