/******************************************************************************
**  Program name:  Club.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Implementation file for the Club class, a derived class of
**                 Space. Represents the outside of the nightclub the player
**                 is trying to get into. Displays one of four text scenes
**                 depending on the context of the gameplay.
*******************************************************************************/

#include <iostream>
#include "Club.hpp"
#include "getMenuChoice.hpp"

/******************************************************************************
** Function name: Club()
** Description:   Constructor for the Club class. Initializes all
**                member strings.
******************************************************************************/

Club::Club(std::string name, std::string introText, std::string altIntroText,
        std::string incompleteOutfitText, std::string loseText,
        std::string winText)
            : Space::Space(std::move(name), std::move(introText),
                    std::move(altIntroText)),
            incompleteOutfitText(std::move(incompleteOutfitText)),
            loseText(std::move(loseText)),
            winText(std::move(winText))
{
    type = club;
}

/******************************************************************************
** Function name: scene()
** Description:   When a player enters the space, this function displays the
**                correct scene depending on the current gameplay state,
**                presents the player with a menu (if the game is not over),
**                and returns the results of the player's menu choice as a
**                NextMove enum. Returns "Exit" if the game is over.
******************************************************************************/

NextMove Club::scene(int& time, int& wallet, Outfit* outfit)
{
    if (visited)
    {
        if (outfit->isComplete())
        {
            if (outfit->isHot())
            {
                std::cout << winText;
                return Exit;
            }
            else
            {
                std::cout << loseText;
                return Exit;
            }
        }
        else
        {
            if (time < 120)
            {
                std::cout << incompleteOutfitText;
                std::cout  << "\n\n";
                std::cout << "Enter 1 to continue your journey\n";
                int choice = getMenuChoice("", 1, 1);
                return West;
            }
            else
            {
                std::cout << loseText << "\n\n";
                return Exit;
            }
        }
    }
    else
    {
        std::cout << introText;
        std::cout  << "\n\n";
        visited = true;
        std::cout << "Enter 1 to begin your journey\n";
        int choice = getMenuChoice("", 1, 1);
        return West;
    }
}