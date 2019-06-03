//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_SPACE_HPP
#define INC_162_FINAL_PROJECT_SPACE_HPP
#include <string>


class Space
{
private:
    Space* neighbors[4]{nullptr};
    std::string name;
    bool visited = false;
public:
    explicit Space(std::string name);
    Space* getNorth();
    Space* getEast();
    Space* getSouth();
    Space* getWest();
    void setNorth(Space* north);
    void setEast(Space* east);
    void setSouth(Space* south);
    void setWest(Space* west);
    std::string getName();
};


#endif //INC_162_FINAL_PROJECT_SPACE_HPP
