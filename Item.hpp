/******************************************************************************
**  Program name:  Item.hpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Header file for the Item struct, which represents
**                 an inventory item inside a Store which the player can buy.
*******************************************************************************/

#ifndef INC_162_FINAL_PROJECT_ITEM_HPP
#define INC_162_FINAL_PROJECT_ITEM_HPP
#include <valarray>
#include <string>

struct Item
{
    std::valarray <int> styles = {0,0,0,0}; // Style vector
    int price;                              // Price of the item
    std::string name;                       // Name of the item
    std::string type;                       // Shorter name of the item
    int category;           // 0 = Shoes 1 = Bottom 2 = Top 3 = Accessory
    Item(std::string name, std::string type, int category, int price,
            std::valarray<int> styles);
    std::string pronoun();
    int strongestStyle();
};

#endif //INC_162_FINAL_PROJECT_ITEM_HPP