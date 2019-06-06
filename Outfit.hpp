//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
#define INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
#include <array>
#include <valarray>
#include "Item.hpp"

class Outfit
{
private:
    std::array <Item*, 4> clothes = {{nullptr}};
public:
    bool isComplete();
    bool isEmpty();
    bool isCategoryTaken(int index);
    bool addItem(Item* purchase);
    std::valarray<int> getClothesTotal();
    bool isHot();
    void areWearing();
    std::string getItemName(int index);
    int strongestStyle();
};

#endif //INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
