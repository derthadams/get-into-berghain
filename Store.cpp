//
// Created by Derth Adams on 2019-06-03.
//

#include <iostream>
#include <iomanip>
#include <utility>
#include <random>
#include <chrono>
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
            tryOn(wallet, outfit, (choice - 1));
            // evaluate (outfit, index)
        }
        else if (choice == inventory.size() + 1)
        {
            outfit->areWearing();
        }
    }
    return static_cast<NextMove>(getExitIndex());
}

void Store::tryOn(int& wallet, Outfit* outfit, int index)
{
    switch (inventory[index]->category)
    {
        case 0:
        {
            std::cout << "You slip out of your tired old shoes and put on the "
                      << inventory[index]->type << ".\n"
                      << "You take a few steps and twirl around as Pascal and "
                      << clerkName << " examine you closely.\n\n";
            break;
        }
        case 3:
        {
            std::cout << "You put on the " << inventory[index]->type
                      << " 1and walk over to the mirror \nto take in the effect. "
                         "You glance back at Pascal and "
                      << clerkName << ".\n\n";
            break;
        }
        default:
        {
            std::cout << "You take the " << inventory[index]->type
                      << " back to the dressing room and put it on.\n"
                         "As you emerge, Pascal and "
                      << clerkName
                      << " are waiting to deliver their verdict.\n\n";
        }
    }
    evaluate(outfit, index);

    int choice = getMenuChoice("1. Buy the " + inventory[index]->type +
            "\n2. Don't.\n\n", 1, 2);
    switch (choice)
    {
        case 1:
        {
            if (inventory[index]->price <= wallet)
            {
                if (outfit->addItem(inventory.at(index)))
                {
                    std::cout << "You say, \"I'll take it! "
                                 "Can I just keep it on?\"\n"
                              << clerkName
                              << " says, \"As you wish.\"\nYou hand over the "
                                 "\u20AC" << inventory[index]->price << ".\n\n";
                    wallet -= inventory[index]->price;
                    inventory.erase(inventory.begin() + index);
                }
                else
                {
                    switch (index)
                    {
                        case 0:
                        {
                            std::cout << "You've already purchased shoes!\n";
                            break;
                        }
                        case 3:
                        {
                            std::cout
                            << "You've already purchased an accessory!\n";
                            break;
                        }
                        default:
                        {
                            std::cout << "You've already purchased a "
                                      << categories[inventory[index]->category]
                                      << "!\n";
                            break;
                        }
                    }

                }
            }
            else
            {
                std::cout << "You look in your wallet and realize you can't"
                             "afford\nthe " << inventory[index]->type
                          << ". Sheepishly you take it off and hand it back to "
                          << clerkName << ".";
            }
            break;
        }
        case 2:
        {
            std::cout << "You say, \"I don't think it's for me\", as you hand "
                         "the " << inventory[index]->type
                         << " back to "
                         << clerkName << ".\n\n";
            break;
        }
    }
}

void Store::evaluate(Outfit*, int index)
{
    int randNum = getRandomNumber();
    if (randNum < 90)
    {
        std::cout << clerkName << " likes it!\n";
    }
    if (randNum < 75)
    {

    }
}

void Store::addItem(Item* item)
{
    inventory.push_back(item);
}

bool Store::isOpen(int time)
{
    return (time <= 120);
}

int Store::getRandomNumber()
{
    auto seed = std::chrono::high_resolution_clock::now()
            .time_since_epoch()
            .count();
    std::mt19937 generator(static_cast<unsigned int>(seed));
    std::uniform_int_distribution<int> distribution(1,100);
    return distribution(generator);
}