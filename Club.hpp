//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_CLUB_HPP
#define INC_162_FINAL_PROJECT_CLUB_HPP
#include "Space.hpp"
#include <string>

class Club : public Space
{
private:
    std::string incompleteOutfitIntroText;
public:
    Club(std::string name);
};


#endif //INC_162_FINAL_PROJECT_CLUB_HPP
