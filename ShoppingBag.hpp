//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
#define INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
#include <array>
#include "Item.hpp"

class ShoppingBag
{
private:
    std::array <Item*, 5> bag = {{nullptr}};
};

#endif //INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
