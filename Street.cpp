//
// Created by Derth Adams on 2019-06-03.
//
#include <iostream>
#include <vector>
#include "Street.hpp"
#include "Store.hpp"
#include "getMenuChoice.hpp"

Street::Street(std::string name, std::string introText,
        std::string altIntroText) : Space::Space(std::move(name),
                std::move(introText), std::move(altIntroText))
{
    type = street;
}

NextMove Street::scene(int& time, int& wallet, Outfit* outfit)
{
//    if (visited)
//    {
//        if (time < 120)
//        {
//            std::cout << altIntroText;
//        }
//        else
//        {
//            std::cout << "The stores are closed.\n";
//        }
//    }
//    else
//    {
//        if (time < 120)
//        {
//            std::cout << introText;
//        }
//        else
//        {
//            std::cout << "The stores are closed.\n";
//        }
//    }
    if (time < 120)
    {
        std::cout << introText;
    }
    else
    {
        std::cout << altIntroText;
    }
    std::cout  << "\n\n";
    visited = true;

    int numItems = 1;
    std::vector<int> menuMap;
    for (int i = 0; i < 4; i++)
    {
        if (neighbors[i])
        {
            if (neighbors[i]->getType() == street)
            {
                std::cout << numItems << ". Walk to ";
                std::cout << neighbors[i]->getName() << "\n";
                menuMap.push_back(i);
                numItems++;

                std::cout << numItems << ". Drive to ";
                std::cout << neighbors[i]->getName() << "\n";
                if (i == 0)
                {
                    menuMap.push_back(4);
                }
                else if (i == 2)
                {
                    menuMap.push_back(5);
                }
                numItems++;
            }
            else if (neighbors[i]->getType() == store)
            {
                if(dynamic_cast<Store*>(neighbors[i])->isOpen(time))
                {
                    std::cout << numItems << ". Visit ";
                    std::cout << neighbors[i]->getName() << "\n";
                    menuMap.push_back(i);
                    numItems++;
                }
            }
            else if (neighbors[i]->getType() == club)
            {
                std::cout << numItems << ". Go back to Berghain\n";
                menuMap.push_back(i);
                numItems++;
            }
        }
    }
    std::cout << numItems << ". Quit Game\n";
    menuMap.push_back(6);
    int choice = getMenuChoice("", 1, numItems);
    return static_cast<NextMove>(menuMap[choice - 1]);
}