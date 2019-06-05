//
// Created by Derth Adams on 2019-06-03.
//
#include <iostream>
#include <vector>
#include "Street.hpp"
#include "getMenuChoice.hpp"

Street::Street(std::string name, std::string introText,
        std::string altIntroText) : Space::Space(name, introText, altIntroText)
{
    type = street;
}

NextMove Street::scene(int time, int& wallet, Outfit* outfit)
{
    if (visited)
    {
        std::cout << altIntroText;
    }
    else
    {
        std::cout << introText;
    }
    std::cout  << "\n\n";
    visited = true;
    int numItems = 0;
    std::vector<int> menuMap;
    for (int i = 0; i < 4; i++)
    {
        if (neighbors[i])
        {
            numItems++;
            menuMap.push_back(i);
            if (neighbors[i]->getType() == street)
            {
                std::cout << numItems << ". Walk to ";
            }
            else
            {
                std::cout << numItems << ". Visit ";
            }
            std::cout << neighbors[i]->getName() << "\n";
        }
    }
    int choice = getMenuChoice("", 1, numItems);
    return static_cast<NextMove>(menuMap[choice - 1]);
}