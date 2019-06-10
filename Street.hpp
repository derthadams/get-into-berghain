/******************************************************************************
**  Program name:  Street.hpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Header file for the Street class, a derived class of
**                 Space. Represents a street the player must pass through
**                 on their way between other Spaces like the club and the
**                 four Stores.
*******************************************************************************/

#ifndef INC_162_FINAL_PROJECT_STREET_HPP
#define INC_162_FINAL_PROJECT_STREET_HPP
#include "Space.hpp"
#include <string>


class Street : public Space
{
public:
    Street(std::string name, std::string introText, std::string altIntroText);
    NextMove scene(int& time, int& wallet, Outfit* outfit) override;
};


#endif //INC_162_FINAL_PROJECT_STREET_HPP