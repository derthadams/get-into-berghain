/******************************************************************************
**  Program name:  Outfit.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Implementation file for the Outfit class, which represents
**                 the collection of Items the player has purchased.
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include "Outfit.hpp"
#include "Item.hpp"
#include "AsciiArt.hpp"
#include "getMenuChoice.hpp"

/******************************************************************************
** Function name: ~Outfit()
** Description:   Destructor for the Outfit class. Walks through the clothes
**                array and deletes Item objects.
******************************************************************************/

Outfit::~Outfit()
{
    for (int i = 0; i < 4; i++)
    {
        if (clothes[i])
        {
            delete clothes[i];
            clothes[i] = nullptr;
        }
    }
}

/******************************************************************************
** Function name: isComplete()
** Description:   Returns true if the player has purchased one of each of
**                the four item categories, false if not.
******************************************************************************/

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

/******************************************************************************
** Function name: isEmpty()
** Description:   Returns true if the player has purchased no Items, false
**                if they've purchased one or more Items.
******************************************************************************/

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

/******************************************************************************
** Function name: isCategoryTaken(int)
** Description:   Takes an integer representing a category of item (Shoes,
**                Bottoms, etc). Returns true if the player has already
**                purchased an item from that category, false if not.
******************************************************************************/

bool Outfit::isCategoryTaken(int index)
{
    return (clothes[index]);
}

/******************************************************************************
** Function name: addItem(Item*)
** Description:   Takes an Item pointer and adds that item to the appropriate
**                slot in the clothes array based on its category.
******************************************************************************/

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

/******************************************************************************
** Function name: getClothesTotal()
** Description:   Returns a valarray representing the elementwise sum of
**                all of the style vectors of the Items in the clothes array.
******************************************************************************/

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

/******************************************************************************
** Function name: isHot()
** Description:   Returns true if one of the elements in the sum vector returned
**                by getClothesTotal >= 100 (ie, if the Items in the clothes
**                array combine to form a cohesive look).
******************************************************************************/

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

/******************************************************************************
** Function name: areWearing()
** Description:   Prints out a summary of the Items purchased so far.
******************************************************************************/

void Outfit::areWearing()
{
    int choice;
    std::cout << "                            What you're wearing now:\n\n";
    std::cout << TOP_DIAL;
    std::cout << PAD05 << std::left << std::setw(12) << "Shoes:"
              << getItemName(0) << "\n";
    std::cout << PAD05 << std::left << std::setw(12) << "Bottom:"
              << getItemName(1) << "\n";
    std::cout << PAD05 << std::left << std::setw(12) << "Top:"
              << getItemName(2) << "\n";
    std::cout << PAD05 << std::left << std::setw(12) << "Accessory:"
              << getItemName(3) << "\n";
    std::cout << BOT_DIAL << "\n\n";
    choice = getMenuChoice("\nEnter 1 to continue:", 1, 100);
}

/******************************************************************************
** Function name: getItemName()
** Description:   Takes an integer representing the index of an Item in the
**                clothes array, returns a string representing the Item's
**                name if an Item exists at that index, "Nothing Special"
**                if no Item exists at the index (meaning that the player
**                is still wearing something from their original outfit
**                Sven rejected at the beginning of the game).
******************************************************************************/

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

/******************************************************************************
** Function name: strongestStyle()
** Description:   Returns an integer representing the look that the Outfit
**                most clearly embodies (ie, the index of the max element in the
**                valarray returned by getClothesTotal()). Used in
**                Store::evaluate() to determine which look the current
**                outfit most clearly embodies.
******************************************************************************/

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