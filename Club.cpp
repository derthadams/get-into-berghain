//
// Created by Derth Adams on 2019-06-03.
//

#include <iostream>
#include "Club.hpp"

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
        return West;
    }
    else if (!visited)
    {
        std::cout << introText;
        std::cout  << "\n\n";
        visited = true;
        return West;
    }
}

