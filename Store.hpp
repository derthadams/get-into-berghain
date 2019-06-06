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
    std::vector <std::string> clerkResponse;
    std::vector <std::string> pascalResponse;
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
    int getRandomNumber(int min, int max);
    void addItem(Item* item) override;
    void addClerkResponse(std::string const&) override;
    void addPascalResponse(std::string const&) override;
    NextMove scene(int& time, int& wallet, Outfit* outfit) override;
    void tryOn(int& wallet, Outfit* outfit, int index);
    void evaluate(Outfit* outfit, int index);
    bool isOpen(int time) override;
    void displayInventory();
    int mainMenu(int& time, int& wallet, Outfit*);
    void logLine(int time, int wallet);
};


#endif //INC_162_FINAL_PROJECT_STORE_HPP
