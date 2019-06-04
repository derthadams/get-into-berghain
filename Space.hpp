//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_SPACE_HPP
#define INC_162_FINAL_PROJECT_SPACE_HPP
#include <string>
#include "Outfit.hpp"

enum SpaceType {club, store, street};
enum Compass {North = 0, East, South, West};

class Space
{
private:
    Space* neighbors[4]{nullptr};
    std::string name;
    bool visited = false;
    std::string introText;
    std::string altIntroText;
protected:
    SpaceType type;
public:
    explicit Space(std::string name);
    virtual ~Space();
    Space* getNorth();
    Space* getEast();
    Space* getSouth();
    Space* getWest();
    void setNorth(Space* north);
    void setEast(Space* east);
    void setSouth(Space* south);
    void setWest(Space* west);
    std::string getName();
    SpaceType getType();
    virtual void intro();
    virtual Compass scene(int time, int& wallet, Outfit* outfit) = 0;
};


#endif //INC_162_FINAL_PROJECT_SPACE_HPP
