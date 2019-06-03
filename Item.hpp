//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_ITEM_HPP
#define INC_162_FINAL_PROJECT_ITEM_HPP
#include <valarray>
#include <string>

struct Item
{
    std::valarray <int> styles;
    std::string name;
    std::string type;
    std::string category;
};

#endif //INC_162_FINAL_PROJECT_ITEM_HPP
