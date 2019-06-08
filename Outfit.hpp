/******************************************************************************
**  Program name:  Outfit.hpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Header file for the Outfit class, which represents
**                 the collection of Items the player has purchased.
*******************************************************************************/

#ifndef INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
#define INC_162_FINAL_PROJECT_SHOPPINGBAG_HPP
#include <array>
#include <valarray>
#include "Item.hpp"

class Outfit
{
private:
    std::array <Item*, 4> clothes = {{nullptr}};    // Pointers to Items the
                                                    // player has purchased
public:
    ~Outfit();
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