//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_STREET_HPP
#define INC_162_FINAL_PROJECT_STREET_HPP
#include "Space.hpp"
#include <string>


class Street : public Space
{
public:
    Street(std::string name);
    Compass scene(int time, int& wallet, Outfit* outfit) override;
};


#endif //INC_162_FINAL_PROJECT_STREET_HPP
