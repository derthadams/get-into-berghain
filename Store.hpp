//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_STORE_HPP
#define INC_162_FINAL_PROJECT_STORE_HPP
#include "Space.hpp"
#include "Item.hpp"
#include <string>
#include <vector>


class Store : public Space
{
private:
    std::vector <Item*> inventory;
    std::string clerkName;
    std::string clerkDescription;
public:
    Store(std::string name);
    std::string getClerkName();
    std::string getClerkDescription();
    Compass scene(int time, int& wallet, Outfit* outfit) override;
};


#endif //INC_162_FINAL_PROJECT_STORE_HPP
