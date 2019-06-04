//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
#define INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
#include <array>
#include "Item.hpp"

class Outfit
{
private:
    std::array <Item*, 4> clothes = {{nullptr}};
public:
    bool isComplete();
    bool addItem(Item* purchase);
};

#endif //INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP