/******************************************************************************
**  Program name:  Club.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Header file for the Club class, a derived class of
**                 Space. Represents the outside of the nightclub the player
**                 is trying to get into. Displays one of four text scenes
**                 depending on the context of the gameplay.
*******************************************************************************/

#ifndef INC_162_FINAL_PROJECT_CLUB_HPP
#define INC_162_FINAL_PROJECT_CLUB_HPP
#include "Space.hpp"
#include <string>

class Club : public Space
{
private:
    std::string incompleteOutfitText;// Scene if player has incomplete outfit
    std::string loseText;            // Scene if player loses game
    std::string winText;             // Scene if player wins game
public:
    Club(std::string name, std::string introText, std::string altIntroText,
            std::string incompleteOutfitText, std::string loseText,
            std::string winText);
    NextMove scene(int& time, int& wallet, Outfit* outfit) override;
};


#endif //INC_162_FINAL_PROJECT_CLUB_HPP