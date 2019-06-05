//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_ITEM_HPP
#define INC_162_FINAL_PROJECT_ITEM_HPP
#include <valarray>
#include <string>

struct Item
{
    std::valarray <int> styles = {0,0,0,0};
    int price;
    std::string name;
    std::string type;
    int category;       // 0 = Shoes 1 = Bottom 2 = Top 3 = Accessory
    Item(std::string name, std::string type, int category, int price,
            std::valarray<int> styles);
    std::string pronoun();
};

#endif //INC_162_FINAL_PROJECT_ITEM_HPP
