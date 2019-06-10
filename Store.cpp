/******************************************************************************
**  Program name:  Store.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Implementation file for the Store class, which is a
**                 derived class of Space. Represents one of the stores the
**                 player is shopping in.
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <utility>
#include <random>
#include <chrono>
#include "Store.hpp"
#include "getMenuChoice.hpp"
#include "Constants.hpp"
#include "AsciiArt.hpp"

/******************************************************************************
** Function name: Store()
** Description:   Constructor for the Space class. Sets member variables to
**                their values.
******************************************************************************/

Store::Store(std::string name, std::string introText,
             std::string altIntroText, std::string clerkName,
             std::string clerkDescription) : Space::Space(std::move(name),
                     std::move(introText), std::move(altIntroText)),
                     clerkName(std::move(clerkName)),
                     clerkDescription(std::move(clerkDescription))
{
    type = store;
}

/******************************************************************************
** Function name: ~Store()
** Description:   Destructor for the Space class. Deletes all the Item
**                objects in the inventory.
******************************************************************************/

Store::~Store()
{
    for (Item* item : inventory)
    {
        delete item;
        item = nullptr;
    }
}

/******************************************************************************
** Function name: getExitIndex()
** Description:   Returns an integer representing the direction of the store's
**                exit. Used in Store::scene().
******************************************************************************/

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

/******************************************************************************
** Function name: scene()
** Description:   Takes integers by reference for the game time, the
**                player's wallet, and a pointer to the Outfit object.
**                Overrides the pure virtual function in Space. Contains the
**                top-level logic for the player's visit to the Store. When
**                the player enters the Store, this function displays the
**                correct scene depending on the current gameplay state, then
**                displays the store's inventory and the main menu in a
**                while loop until the player either completes their outfit,
**                chooses to exit the store or chooses to quit the game.
******************************************************************************/

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

    // While player has chosen an inventory item and not "Exit" or "Quit"
    while (choice < inventory.size() + 2)
    {
        logLine(time, wallet);
        // If the outfit is complete, jump back to Berghain
        if (outfit->isComplete())
        {
            std::cout << "Pascal says, \"Honey, your outfit is complete! "
                         "Let's head back to Berghain!\"\n\n";
            choice = getMenuChoice("1. Exit store\n", 1, 100);
            return Home;
        }
        // If the outfit isn't complete, display the store inventory
        else
        {
            std::cout << "Available Items: \n";
            displayInventory();
            choice = mainMenu(time, wallet, outfit);
        }
    }

    // Player chooses to exit the store
    if (choice == inventory.size() + 2)
    {
        return static_cast<NextMove>(getExitIndex());
    }

    // Player chooses to quit the game
    else if (choice == inventory.size() + 3)
    {
        return Exit;
    }
}

/******************************************************************************
** Function name: tryOn()
** Description:   Takes an integer by reference for the
**                player's wallet, a pointer to the Outfit object, and an int
**                representing the index of the chosen clothing item in the
**                Store's inventory vector. Simulates the player trying on an
**                article of clothing, getting feedback from the clerk and
**                Pascal, and choosing whether or not to buy it. If the player
**                chooses to buy and has enough money in their wallet, the
**                item is removed from inventory and placed in the player's
**                Outfit object.
******************************************************************************/

void Store::tryOn(int& wallet, Outfit* outfit, int index)
{
    switch (inventory[index]->category)
    {
        // The player chose to try on shoes
        case 0:
        {
            std::cout << "You slip out of your tired old shoes and put on the "
                      << inventory[index]->type << ".\n"
                      << "You take a few steps and twirl around as Pascal and "
                      << clerkName << "\n" << "examine you closely.\n\n";
            break;
        }
        // The player chose to try on an accessory
        case 3:
        {
            std::cout << "You put on the " << inventory[index]->type
                      << " and walk over to the mirror to have a look.\n"
                      << "You glance back at Pascal and "
                      << clerkName << ".\n\n";
            break;
        }
        // The player chose to try on a top or bottom
        default:
        {
            std::cout << "You take the " << inventory[index]->type
                      << " back to the dressing room and put "
                      << inventory[index]->pronoun() << " on.\n"
                      << "As you emerge, Pascal and "
                      << clerkName
                      << " are waiting to deliver their verdict.\n\n";
        }
    }

    // Call evaluate() to get the clerk and Pascal's reactions
    evaluate(outfit, index);

    // Give player the choice whether or not to buy the item
    std::cout << TOP_DIVIDER;
    int choice = getMenuChoice(PAD05 + "1. Buy the " + inventory[index]->type +
            "\n" + PAD05 + "2. Put " + inventory[index]->pronoun() + " back.\n"
            + BOT_DIVIDER, 1, 2);
    switch (choice)
    {
        case 1:
        {
            // If player chooses to buy and has enough money
            if (inventory[index]->price <= wallet)
            {
                // Transfer the item from inventory to player's outfit
                outfit->addItem(inventory.at(index));

                // Display message
                std::cout << TOP_DIAL;
                std::cout << PAD05 << "You say, \"I'll take "
                          << inventory[index]->pronoun() << "! "
                          << "Can I just keep "
                          << inventory[index]->pronoun() << " on?\"\n"
                          << PAD05 << clerkName
                          << " says, \"As you wish.\"\n"
                          << PAD05 << "You hand over the "
                             "\u20AC" << inventory[index]->price << ".\n";
                wallet -= inventory[index]->price;
                std::cout << BOT_DIAL<< "\n";

                // Erase item pointer from inventory
                inventory.erase(inventory.begin() + index);
            }
            else
            {
                // If the player wants to buy but doesn't have the money,
                // display message
                std::cout << TOP_DIAL << PAD05
                          << "You look in your wallet and realize you can't "
                          << "afford\n" << PAD05 << "the "
                          << inventory[index]->type
                          << ".\n" << PAD05 << "Sheepishly you take "
                          << inventory[index]->pronoun()
                          << " off and hand " << inventory[index]->pronoun()
                          << " back to "
                          << clerkName << ".\n" << BOT_DIAL << "\n";
            }
            break;
        }
        case 2:
        {
            // Player decides not to buy
            std::cout << TOP_DIAL << PAD05;
            std::cout << "You say, \"I don't think it's my style\", as you hand "
                         "the\n" << PAD05 << inventory[index]->type
                         << " back to "
                         << clerkName << ".\n" << BOT_DIAL << "\n";
            break;
        }
    }
}

/******************************************************************************
** Function name: evaluate()
** Description:   Takes a pointer to the player's Outfit object and an int
**                representing the index in the store's inventory vector of the
**                Item they're currently trying on. Simulates the store clerk
**                and Pascal giving their reactions to seeing the player
**                wearing the item. The store clerk will give a positive
**                reaction 90% of the time regardless of whether the item
**                contributes to a cohesive look. Pascal will give good advice
**                75% of the time.
******************************************************************************/

void Store::evaluate(Outfit* outfit, int index)
{
    // Pick random number used to calculate clerk's response type
    int randNum = getRandomNumber(1, 100);

    // Pick random number to choose one of three positive/negative responses
    // from clerk
    int response = getRandomNumber(0, 2);

    // Clerk gives a positive response 90% of the time
    if (randNum < 90)
    {
        // Positive response
        std::cout << clerkName << " says, \""
                  << clerkResponse.at(response) << "\"\n" ;
    }
    else
    {
        // Negative response
        std::cout << clerkName << " says, \""
                  << clerkResponse.at(response + 3) << "\"\n" ;
    }

    // Pick random number used to calculate Pascal's response type
    randNum = getRandomNumber(1, 100);

    // Pick random number to choose one of three positive/negative responses
    // from Pascal
    response = getRandomNumber(0, 2);

    // Calculate the "right answer" for whether buying an item  will contribute
    // to the player winning the game
    bool rightAnswer = false;       // rightAnswer is true if buying the item
                                    // will contribute to a win, false
                                    // if it won't

    // If the player has no items, any item will contribute to a win, so
    // set rightAnswer to true.
    if (outfit->isEmpty())
    {
        rightAnswer = true;
    }
    // If the player has items in the outfit already
    else
    {
        // Does the dominant style of the outfit equal the item's
        // dominant style? If it does, rightAnswer is true, if not, false
        rightAnswer = (inventory[index]->strongestStyle()
                        == outfit->strongestStyle());
    }

    // Pascal gives good advice 75% of the time
    if (randNum < 75)
    {
        // Good advice
        std::cout << "Pascal says, \"";
        // If the "right answer" to the question of whether to buy the item
        // is "yes", give a positive response
        if (rightAnswer)
        {
            std::cout << pascalResponse.at(response) << "\"\n";
        }
        // If "no", give a negative response
        else
        {
            std::cout << pascalResponse.at(response + 3) << "\"\n";
        }
    }
    else
    {
        // Bad advice
        std::cout << "Pascal exclaims, \"";
        // If the "right answer" to the question of whether to buy the item
        // is "yes", give a negative response
        if (rightAnswer)
        {
            std::cout << pascalResponse.at(response + 3) << "\"\n";
        }
        // If "no", give a positive response
        else
        {
            std::cout << pascalResponse.at(response) << "\"\n";
        }
    }
    std::cout << "\n";
}

/******************************************************************************
** Function name: addItem()
** Description:   Takes a pointer to Item, adds the item to the Store's
**                inventory vector. Used in Game::loadStore() to set up the
**                store initially.
******************************************************************************/

void Store::addItem(Item* item)
{
    inventory.push_back(item);
}

/******************************************************************************
** Function name: addClerkResponse()
** Description:   Takes a string by const reference, adds the string to the
**                clerkResponse vector. Used in Game::loadStore() to set up the
**                store initially.
******************************************************************************/

void Store::addClerkResponse(std::string const& response)
{
    clerkResponse.push_back(response);
}

/******************************************************************************
** Function name: addPascalResponse()
** Description:   Takes a string by const reference, adds the string to the
**                pascalResponse vector. Used in Game::loadStore() to set up the
**                store initially.
******************************************************************************/

void Store::addPascalResponse(std::string const& response)
{
    pascalResponse.push_back(response);
}

/******************************************************************************
** Function name: isOpen()
** Description:   Returns true if the store is open (ie, if the time is less
**                than 21:00)
******************************************************************************/

bool Store::isOpen(int time)
{
    return (time < TIME_LIMIT);
}

/******************************************************************************
** Function name: getRandomNumber()
** Description:   Takes two integers representing the min and max bounds for
**                the desired random number, returns an int random number.
**                Used in Store::evaluate().
******************************************************************************/

int Store::getRandomNumber(int min, int max)
{
    auto seed = std::chrono::high_resolution_clock::now()
            .time_since_epoch()
            .count();
    std::mt19937 generator(static_cast<unsigned int>(seed));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

/******************************************************************************
** Function name: displayInventory()
** Description:   Displays a numbered list of all the items in the store's
**                inventory, arranged by category.
******************************************************************************/

void Store::displayInventory()
{
    int categoryIndex = -1;
    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory.at(i)->category != categoryIndex)
        {
            categoryIndex = inventory.at(i)->category;
            std::cout << CAT_HEAD[categoryIndex];
        }
        std::cout << PAD03 << std::left << std::setw(5)
                  << std::to_string(i + 1) + "."
                  << std::setw(62)
                  << inventory.at(i)->name << std::setw(5)
                  << "   (\u20AC" << inventory.at(i)->price << ")\n";
    }
    std::cout << "\n";
}

/******************************************************************************
** Function name: mainMenu()
** Description:   Takes integers by reference representing the game time and
**                the player's wallet, and a pointer to the player's Outfit.
**                Implements the menu for the main while loop in
**                Store::scene(). Returns an integer representing the player's
**                menu choice.
******************************************************************************/

int Store::mainMenu(int& time, int& wallet, Outfit* outfit)
{
    int choice;     // The player's menu choice

    // Display main menu
    std::cout << TOP_DIVIDER;
    std::cout << PAD05 << "To try on an item, enter the item's number.\n\n";
    std::cout << PAD05 << inventory.size() + 1
              << ". Review what you're wearing now\n";
    std::cout << PAD05 << inventory.size() + 2
              << ". Exit store\n";
    std::cout << PAD05 << inventory.size() + 3
              << ". Quit Game\n";
    std::cout << BOT_DIVIDER;

    // Get choice
    choice = getMenuChoice("", 1, static_cast<int>(inventory.size()) + 3);

    // If the player decides to try on an item
    if (choice <= inventory.size())
    {
        // Check whether the player has already purchased an item from that
        // category
        int categoryIndex = inventory[choice - 1]->category;
        // If the player already has an item from that category
        if (outfit->isCategoryTaken(categoryIndex))
        {
            // Display a warning message (customized to the category of item)
            std::cout << TOP_DIAL;
            switch (categoryIndex)
            {
                case 0:
                {
                    std::cout << PAD05 << "You've already purchased shoes!\n";
                    break;
                }
                case 3:
                {
                    std::cout
                            << PAD05 << "You've already purchased an "
                                        "accessory!\n";
                    break;
                }
                default:
                {
                    std::cout << PAD05 << "You've already purchased a "
                              << categories[categoryIndex]
                              << "!\n";
                    break;
                }
            }
            std::cout
                    << PAD05 << "Try selecting something from a different "
                                "category.\n"
                    << BOT_DIAL << "\n";
        }
        // If the player does not already have an item from that category,
        // call tryOn() to enter the trying-on simulation.
        else
        {
            time += 5;
            tryOn(wallet, outfit, (choice - 1));
        }
    }
    // If player chooses to review their purchases, call Outfit::areWearing()
    // to display the items.
    else if (choice == inventory.size() + 1)
    {
        outfit->areWearing();
    }
    // Return the player's menu choice back to Store::scene()
    return choice;
}

/******************************************************************************
** Function name: logline()
** Description:   Takes in two ints representing the current time and the
**                amount in the player's wallet.
**                Overrides virtual logLine() function in Space.
**                Displays a status logline indicating the current time,
**                minutes left until all the stores close, the player's
**                current location, and amount of cash left.
**                If the store has closed while the player is still in it,
**                displays a message telling them they can stay until they've
**                made a decision.
*******************************************************************************/

void Store::logLine(int time, int wallet)
{
    std::cout << DINGBAT << std::left << std::setw(11) << "Time:"
              << std::setw(2) << START_HOUR + (time / 60) << ":";
    if (time % 60 < 10)
    {
        std::cout << "0";
    }
    std::cout << (time % 60);
    if (time >= 0 && time < TIME_LIMIT)
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

    // If store has closed while player is still inside
    if (time >= TIME_LIMIT)
    {
        std::cout << TOP_DIAL;
        std::cout << PAD10 << clerkName
                  << " says, \"The store is now closed, but you can keep\n"
                  << PAD10 << "looking if you want.\"\n";
        std::cout << BOT_DIAL << "\n";
    }
}