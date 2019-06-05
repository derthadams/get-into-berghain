//
// Created by Derth Adams on 2019-06-03.
//

#include <iostream>
#include "Club.hpp"
#include "getMenuChoice.hpp"

Club::Club(std::string name, std::string introText, std::string altIntroText,
        std::string incompleteOutfitText, std::string loseText,
        std::string winText)
            : Space::Space(name, introText, altIntroText),
            incompleteOutfitText(incompleteOutfitText), loseText(loseText),
            winText(winText)
{
    type = club;
}

NextMove Club::scene(int time, int& wallet, Outfit* outfit)
{
    if (visited && outfit->isComplete())
    {
        std::cout << altIntroText;
        std::cout  << "\n\n";
        return West;
    }
    else if (visited && !outfit->isComplete())
    {
        std::cout << incompleteOutfitText;
        std::cout  << "\n\n";
        std::cout << "Enter 1 to continue your journey\n";
        int choice = getMenuChoice("", 1, 1);
        return West;
    }
    else if (!visited)
    {
        std::cout << introText;
        std::cout  << "\n\n";
        visited = true;
        std::cout << "Enter 1 to begin your journey\n";
        int choice = getMenuChoice("", 1, 1);
        return West;
    }
}

