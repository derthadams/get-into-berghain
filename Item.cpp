/******************************************************************************
**  Program name:  Item.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Implementation file for the Item struct, which represents
**                 an inventory item inside a Store which the player can buy.
*******************************************************************************/

#include "Item.hpp"

/******************************************************************************
** Function name: Item()
** Description:   Constructor for the Item class. Sets all data members to
**                their values.
******************************************************************************/

Item::Item(std::string name, std::string type, int category, int price,
           std::valarray<int> styles) : name(std::move(name)),
           type(std::move(type)), category(category),
           price(price), styles(std::move(styles))
           {
           }

/******************************************************************************
** Function name: pronoun()
** Description:   Returns a string, either "them" or "it", depending on whether
**                the item is plural or singular. Used in the Store class
**                to construct grammatical sentences when referring to Items.
******************************************************************************/

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

/******************************************************************************
** Function name: strongestStyle()
** Description:   Returns an integer representing the index of the max element
**                of the style vector. Represents the "look" that the Item
**                contributes most strongly to. Used in Store::evaluate() to
**                determine whether an Item's dominant style is the same as
**                the outfit's overall dominant style.
******************************************************************************/

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