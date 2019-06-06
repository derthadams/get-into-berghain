//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_GAME_HPP
#define INC_162_FINAL_PROJECT_GAME_HPP
#include <array>
#include "Space.hpp"
#include "Item.hpp"
#include "constants.hpp"

class Game
{
private:

    int time = 0;
    int wallet = 200;
    Outfit outfit;
    Space* here{nullptr};
    Space* home{nullptr};
public:
    Game();
    ~Game();
    void walkNorth();
    void walkEast();
    void walkSouth();
    void walkWest();
    void driveNorth();
    void driveSouth();
    void start();
    void play();
    void logLine();
    Space* loadStore(std::string filename);
    Space* loadClub(std::string filename);
    Space* loadStreet(std::string filename);
};


#endif //INC_162_FINAL_PROJECT_GAME_HPP