/******************************************************************************
**  Program name:  Store.hpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Header file for the Store class, which is a
**                 derived class of Space. Represents one of the stores the
**                 player is shopping in.
*******************************************************************************/

#ifndef INC_162_FINAL_PROJECT_STORE_HPP
#define INC_162_FINAL_PROJECT_STORE_HPP
#include "Space.hpp"
#include "Item.hpp"
#include <string>
#include <vector>

class Store : public Space
{
private:
    std::vector <Item*> inventory;  // Store's inventory of Item objects
    std::string clerkName;          // Name of Store's clerk
    std::string clerkDescription;   // Description of Store's clerk
    std::vector <std::string> clerkResponse;    // Clerk's possible reactions
                                                // to player trying on an item
    std::vector <std::string> pascalResponse;   // Pascal's possible reactions
                                                // to player trying on an item
    const std::string categories[4] =           // Categories of items
            {"Shoes", "Bottom", "Top", "Accessories"};
public:
    Store(std::string name, std::string introText,
          std::string altIntroText, std::string clerkName,
          std::string clerkDescription);
    ~Store() override;
    int getExitIndex();
    int getRandomNumber(int min, int max);
    void addItem(Item* item);
    void addClerkResponse(std::string const&);
    void addPascalResponse(std::string const&);
    NextMove scene(int& time, int& wallet, Outfit* outfit) override;
    void tryOn(int& wallet, Outfit* outfit, int index);
    void evaluate(Outfit* outfit, int index);
    bool isOpen(int time);
    void displayInventory();
    int mainMenu(int& time, int& wallet, Outfit*);
    void logLine(int time, int wallet) override;
};

#endif //INC_162_FINAL_PROJECT_STORE_HPP