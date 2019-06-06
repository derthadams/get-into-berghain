//
// Created by Derth Adams on 2019-06-03.
//

#include "Item.hpp"

Item::Item(std::string name, std::string type, int category, int price,
           std::valarray<int> styles) : name(std::move(name)),
           type(std::move(type)), category(category),
           price(price), styles(std::move(styles))
           {
           }

std::string Item::pronoun()
{
    if (type.back() == 's' || type.back() == 'n')
    {
        return "them";
    }
    else
    {
        return "it";
    }
}

int Item::strongestStyle()
{
    for (int i = 0; i < 3; i++)
    {
        if (styles[i] == styles.max())
        {
            return i;
        }
    }
    return -1;
}