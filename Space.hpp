//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_SPACE_HPP
#define INC_162_FINAL_PROJECT_SPACE_HPP
#include <string>
#include "Outfit.hpp"

enum SpaceType {club, store, street};
enum NextMove {North = 0, East, South, West, DriveNorth, DriveSouth, Exit, Home};

class Space
{
protected:
    Space* neighbors[4]{nullptr};
    std::string name;
    std::string introText;
    std::string altIntroText;
    SpaceType type;
    bool visited = false;
public:
    explicit Space(std::string name, std::string introText,
            std::string altIntroText);
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
    virtual NextMove scene(int& time, int& wallet, Outfit* outfit) = 0;
    virtual void addItem(Item*);
    virtual bool isOpen(int time);
};


#endif //INC_162_FINAL_PROJECT_SPACE_HPP
