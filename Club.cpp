//
// Created by Derth Adams on 2019-06-03.
//

#include <iostream>
#include "Club.hpp"
#include "getMenuChoice.hpp"

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
            if (time <=120)
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

//NextMove Club::scene(int time, int& wallet, Outfit* outfit)
//{
//    if (visited && outfit->isComplete())
//    {
//        if (outfit->isHot())
//        {
//            std::cout << winText;
//            return Exit;
//        }
//        else
//        {
//            std::cout << loseText;
//            return Exit;
//        }
//    }
//    else if (visited && !outfit->isComplete())
//    {
//        if (time <=120)
//        {
//            std::cout << incompleteOutfitText;
//            std::cout  << "\n\n";
//            std::cout << "Enter 1 to continue your journey\n";
//            int choice = getMenuChoice("", 1, 1);
//            return West;
//        }
//        else
//        {
//            std::cout << loseText << "\n\n";
//            return Exit;
//        }
//    }
//    else if (!visited)
//    {
//        std::cout << introText;
//        std::cout  << "\n\n";
//        visited = true;
//        std::cout << "Enter 1 to begin your journey\n";
//        int choice = getMenuChoice("", 1, 1);
//        return West;
//    }
//}

