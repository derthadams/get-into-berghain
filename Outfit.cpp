//
// Created by Derth Adams on 2019-06-03.
//

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
        total += clothes[i]->styles;
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