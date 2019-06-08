/******************************************************************************
**  Program name:  Space.hpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Implementation file for the Space class, which is the
**                 abstract base class representing the spaces the player
**                 interacts with in the "Get Into Berghain" game.
*******************************************************************************/

#ifndef INC_162_FINAL_PROJECT_SPACE_HPP
#define INC_162_FINAL_PROJECT_SPACE_HPP
#include <string>
#include "Outfit.hpp"

enum SpaceType {club, store, street};           // Subclass of the Space
enum NextMove {North = 0, East, South, West,    // Enum used as the return
        DriveNorth, DriveSouth, Exit, Home};    // value of Space::scene()

class Space
{
protected:
    Space* neighbors[4]{nullptr};   // Pointers to the four adjacent Spaces
    std::string name;               // Name of the Space
    std::string introText;          // Text displayed when the player arrives
    std::string altIntroText;       // Intro text displayed under different
                                    // circumstances
    SpaceType type;                 // Subclass of the Space
    bool visited = false;           // Has the player visited the Space before
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
    virtual void logLine(int time, int wallet);
};


#endif //INC_162_FINAL_PROJECT_SPACE_HPP