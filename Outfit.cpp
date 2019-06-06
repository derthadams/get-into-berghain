//
// Created by Derth Adams on 2019-06-03.
//
#include <iostream>
#include <iomanip>
#include "Outfit.hpp"
#include "Item.hpp"

bool Outfit::isComplete()
{
    for (int i = 0; i < 4; i++)
    {
        if (!clothes[i])
        {
            return false;
        }
    }
    return true;
}

bool Outfit::isEmpty()
{
    for (int i = 0; i < 4; i++)
    {
        if (clothes[i])
        {
            return false;
        }
    }
    return true;
}

bool Outfit::addItem(Item* purchase)
{
    if (clothes[purchase->category])
    {
        return false;
    }
    else
    {
        clothes[purchase->category] = purchase;
        return true;
    }
}

std::valarray<int> Outfit::getClothesTotal()
{
    std::valarray<int> total = {0,0,0,0};
    for (int i = 0; i < 4; i++)
    {
        if (clothes[i])
        {
            total += clothes[i]->styles;
        }
    }
    return total;
}

bool Outfit::isHot()
{
    std::valarray<int> total = getClothesTotal();
    for (int i = 0; i < 3; i++)
    {
        if (total[i] >= 100)
        {
            return true;
        }
    }
    return false;
}

void Outfit::areWearing()
{
    std::cout << "*** What you're wearing now ***\n";
    std::cout << std::left << std::setw(12) << "Shoes:"
              << getItemName(0) << "\n";
    std::cout << std::left << std::setw(12) << "Bottom:"
              << getItemName(1) << "\n";
    std::cout << std::left << std::setw(12) << "Top:"
              << getItemName(2) << "\n";
    std::cout << std::left << std::setw(12) << "Accessory:"
              << getItemName(3) << "\n\n";
}

std::string Outfit::getItemName(int index)
{
    if (clothes[index])
    {
        return clothes[index]->name;
    }
    else
    {
        return "Nothing special";
    }
}

int Outfit::strongestStyle()
{
    for (int i = 0; i < 3; i++)
    {
        if (getClothesTotal()[i] == getClothesTotal().max())
        {
            return i;
        }
    }
    return -1;
}