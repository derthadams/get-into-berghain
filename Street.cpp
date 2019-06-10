/******************************************************************************
**  Program name:  Street.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Implementation file for the Street class, a derived class of
**                 Space. Represents a street the player must pass through
**                 on their way between other Spaces like the club and the
**                 four Stores.
*******************************************************************************/

#include <iostream>
#include <vector>
#include "Street.hpp"
#include "Store.hpp"
#include "getMenuChoice.hpp"
#include "AsciiArt.hpp"

/******************************************************************************
** Function name: Street()
** Description:   Constructor for the Street class. Initializes all
**                member strings.
******************************************************************************/

Street::Street(std::string name, std::string introText,
        std::string altIntroText) : Space::Space(std::move(name),
                std::move(introText), std::move(altIntroText))
{
    type = street;
}

/******************************************************************************
** Function name: scene()
** Description:   Takes integers by reference for the game time, the
**                player's wallet, and a pointer to the Outfit object.
**                Overrides the pure virtual function in Space. Contains the
**                top-level logic for the player's visit to the Street. When
**                the player enters the Street, this function displays the
**                correct scene depending on the current gameplay state, then
**                displays a menu with a list of places the player can go.
******************************************************************************/

NextMove Street::scene(int& time, int& wallet, Outfit* outfit)
{
    // If the stores are still open, display main intro text
    if (time < 120)
    {
        std::cout << introText;
    }
    // If the stores have closed, display alt intro text
    else
    {
        std::cout << altIntroText;
    }
    std::cout  << "\n\n";
    visited = true;

    // Display menu with options for all currently available Spaces
    // adjacent to the Street
    std::cout << TOP_DIVIDER;
    int numItems = 1;           // Number of available spaces
    std::vector<int> menuMap;   // Vector of ints representing the
                                // NextMove enum represented by each
                                // available space in the menu

    // Iterate through all four possible adjacent Spaces
    for (int i = 0; i < 4; i++)
    {
        // If there's an adjacent Space in that direction
        if (neighbors[i])
        {
            // If it's a street, display the "walk to" and "drive to" options
            if (neighbors[i]->getType() == street)
            {
                std::cout << PAD05 << numItems << ". Walk to ";
                std::cout << neighbors[i]->getName() << "\n";
                menuMap.push_back(i);
                numItems++;

                std::cout << PAD05 << numItems << ". Drive to ";
                std::cout << neighbors[i]->getName() << "\n";

                // If adjacent space is to the North, add "DriveNorth" to
                // menu map
                if (i == 0)
                {
                    menuMap.push_back(4);
                }
                // If adjacent space is to the North, add "DriveSouth" to
                // menu map
                else if (i == 2)
                {
                    menuMap.push_back(5);
                }
                numItems++;
            }
            // If it's a store
            else if (neighbors[i]->getType() == store)
            {
                // If the store is open, display menu item for the store
                if(dynamic_cast<Store*>(neighbors[i])->isOpen(time))
                {
                    std::cout << PAD05 << numItems << ". Visit ";
                    std::cout << neighbors[i]->getName() << "\n";
                    menuMap.push_back(i);
                    numItems++;
                }
            }
            // If it's a club, display menu item for club
            else if (neighbors[i]->getType() == club)
            {
                std::cout << PAD05 << numItems << ". Go back to Berghain\n";
                menuMap.push_back(i);
                numItems++;
            }
        }
    }
    // Display menu item for quitting game
    std::cout << PAD05 << numItems << ". Quit Game\n";
    menuMap.push_back(6);
    std::cout << BOT_DIVIDER;

    // Get player's choice, return the NextMove enum corresponding to choice.
    int choice = getMenuChoice("", 1, numItems);
    return static_cast<NextMove>(menuMap[choice - 1]);
}