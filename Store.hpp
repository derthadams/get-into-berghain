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
    const std::string categories[4] =
            {"Shoes", "Bottoms", "Tops", "Accessories"};
public:
    Store(std::string name, std::string introText,
          std::string altIntroText, std::string clerkName,
          std::string clerkDescription);
    ~Store() override;
    std::string getClerkName();
    std::string getClerkDescription();
    int getExitIndex();
    int getRandomNumber();
    void addItem(Item* item) override;
    NextMove scene(int time, int& wallet, Outfit* outfit) override;
    void tryOn(int& wallet, Outfit* outfit, int index);
    void evaluate(Outfit* outfit, int index);
    bool isOpen(int time) override;
    void displayInventory();
    int mainMenu(int&, Outfit*);
};


#endif //INC_162_FINAL_PROJECT_STORE_HPP
