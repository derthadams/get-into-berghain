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

NextMove Store::scene(int& time, int& wallet, Outfit* outfit)
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
    displayInventory();

    int choice = 0;
    choice = mainMenu(time, wallet, outfit);

    while (choice != inventory.size() + 2)
    {
        logLine(time, wallet);
        if (outfit->isComplete())
        {
            std::cout << "Pascal says, \"Honey, your outfit is complete! "
                         "Let's head back to Berghain!\"\n\n";
            choice = getMenuChoice("1. Exit store\n", 1, 1);
            return Home;
        }
        else
        {
            std::cout << "Available Items: \n";
            displayInventory();
            choice = mainMenu(time, wallet, outfit);
        }
    }
    return static_cast<NextMove>(getExitIndex());
}

void Store::tryOn(int& wallet, Outfit* outfit, int index)
{
    std::cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n";
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
                      << " and walk over to the mirror to have a look.\n"
                         "You glance back at Pascal and "
                      << clerkName << ".\n\n";
            break;
        }
        default:
        {
            std::cout << "You take the " << inventory[index]->type
                      << " back to the dressing room and put "
                      << inventory[index]->pronoun() << " on.\n"
                         "As you emerge, Pascal and "
                      << clerkName
                      << " are waiting to deliver their verdict.\n\n";
        }
    }
    evaluate(outfit, index);

    int choice = getMenuChoice("1. Buy the " + inventory[index]->type +
            "\n2. Put " + inventory[index]->pronoun() + " back.\n\n", 1, 2);
    switch (choice)
    {
        case 1:
        {
            if (inventory[index]->price <= wallet)
            {
                if (outfit->addItem(inventory.at(index)))
                {
                    std::cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n";
                    std::cout << "You say, \"I'll take "
                              << inventory[index]->pronoun() << "! "
                              << "Can I just keep "
                              << inventory[index]->pronoun() << " on?\"\n"
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
                std::cout << "You look in your wallet and realize you can't "
                             "afford\nthe " << inventory[index]->type
                          << ". Sheepishly you take "
                          << inventory[index]->pronoun()
                          << " off and hand " << inventory[index]->pronoun()
                          << " back to "
                          << clerkName << ".\n\n";
            }
            break;
        }
        case 2:
        {
            std::cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n";
            std::cout << "You say, \"I don't think it's my style\", as you hand "
                         "the " << inventory[index]->type
                         << " back to "
                         << clerkName << ".\n\n";
            break;
        }
    }
}

void Store::evaluate(Outfit* outfit, int index)
{
    int randNum = getRandomNumber(1, 100);
    int response = getRandomNumber(0, 2);
    if (randNum < 90)
    {

        std::cout << clerkName << " says, \""
                  << clerkResponse.at(response) << "\"\n" ;
    }
    else
    {
        std::cout << clerkName << " says, \""
                  << clerkResponse.at(response + 3) << "\"\n" ;
    }
    bool rightAnswer = false;

    if (outfit->isEmpty())
    {
        rightAnswer = true;
    }
    else
    {
        rightAnswer = (inventory[index]->strongestStyle()
                        == outfit->strongestStyle());
        std::cout << "Strongest style index so far: "
                  << outfit->strongestStyle() << "\n";
    }
    if (randNum < 75)
    {
        // Good advice
        std::cout << "Pascal says, \"";
        if (rightAnswer)
        {
            std::cout << pascalResponse.at(response) << "\"\n\n";
        }
        else
        {
            std::cout << pascalResponse.at(response + 3) << "\"\n\n";
        }
    }
    else
    {
        // Bad advice
        std::cout << "Pascal exclaims, \"";
        if (rightAnswer)
        {
            std::cout << pascalResponse.at(response + 3) << "\"\n\n";
        }
        else
        {
            std::cout << pascalResponse.at(response) << "\"\n\n";
        }
    }

}

void Store::addItem(Item* item)
{
    inventory.push_back(item);
}

void Store::addClerkResponse(std::string const& response)
{
    clerkResponse.push_back(response);
}

void Store::addPascalResponse(std::string const& response)
{
    pascalResponse.push_back(response);
}

bool Store::isOpen(int time)
{
    return (time <= 120);
}

int Store::getRandomNumber(int min, int max)
{
    auto seed = std::chrono::high_resolution_clock::now()
            .time_since_epoch()
            .count();
    std::mt19937 generator(static_cast<unsigned int>(seed));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void Store::displayInventory()
{
    int categoryIndex = -1;
    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory.at(i)->category != categoryIndex)
        {

            categoryIndex = inventory.at(i)->category;
            std::cout << "\n** " << categories[categoryIndex] << " **\n";
        }
        std::cout << std::left << std::setw(5) << std::to_string(i + 1) + "."
                  << std::setw(62)
                  << inventory.at(i)->name << std::setw(5)
                  << "   (\u20AC" << inventory.at(i)->price << ")\n";
    }
    std::cout << "\n";
}

int Store::mainMenu(int& time, int& wallet, Outfit* outfit)
{
    int choice;
//    std::cout << "You have \u20AC" << wallet << " left to spend.\n\n";
    std::cout << "What would you like to do?\n\n";
    std::cout << "To try on an item, enter the item's number.\n";
    std::cout << inventory.size() + 1
              << ". Review what you're wearing now\n";
    std::cout << inventory.size() + 2
              << ". Exit store\n";
    choice = getMenuChoice("", 1, static_cast<int>(inventory.size()) + 2);
    if (choice <= inventory.size())
    {
        int categoryIndex = inventory[choice - 1]->category;
        if (outfit->isCategoryTaken(categoryIndex))
        {
            std::cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n";
            switch (categoryIndex)
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
                              << categories[categoryIndex]
                              << "!\n";
                    break;
                }
            }
            std::cout
                    << "Try selecting something from a different category.\n\n";
        }
        else
        {
            time += 5;
            tryOn(wallet, outfit, (choice - 1));
        }
    }
    else if (choice == inventory.size() + 1)
    {
        std::cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n";
        outfit->areWearing();
    }
    return choice;
}

void Store::logLine(int time, int wallet)
{
    std::cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n";
    std::cout << "Time:      " << 19 + (time / 60) << ":";
    if (time % 60 < 10)
    {
        std::cout << "0";
    }
    std::cout << (time % 60);
    if (time >= 0 && time <=120)
    {
        std::cout  << " (" << 120 - time
                   << " minutes left)\n";
    }
    else
    {
        std::cout <<
                  " (Your time is up)" << "\n";
    }
    std::cout << "Place:     " << name << "\n"
              << "Cash left: \u20AC" << wallet << "\n\n";
}