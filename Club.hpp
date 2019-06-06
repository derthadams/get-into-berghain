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
    std::string incompleteOutfitText;
    std::string loseText;
    std::string winText;
public:
    Club(std::string name, std::string introText, std::string altIntroText,
            std::string incompleteOutfitText, std::string loseText,
            std::string winText);
    NextMove scene(int& time, int& wallet, Outfit* outfit) override;
};


#endif //INC_162_FINAL_PROJECT_CLUB_HPP
