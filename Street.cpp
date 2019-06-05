//
// Created by Derth Adams on 2019-06-03.
//
#include <iostream>
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
    for (int i = 1; i <=4; i++)
    {
        if (neighbors[i-1]->getType() == street)
        {
            std::cout << i << ". Walk to ";
        }
        else
        {
            std::cout << i << ". Visit ";
        }
        std::cout << neighbors[i-1]->getName() << "\n";
    }
    int choice = getMenuChoice("", 1, 4);
    return static_cast<NextMove>(choice - 1);
}