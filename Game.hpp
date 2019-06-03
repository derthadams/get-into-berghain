//
// Created by Derth Adams on 2019-06-03.
//

#ifndef INC_162_FINAL_PROJECT_GAME_HPP
#define INC_162_FINAL_PROJECT_GAME_HPP
#include <array>
#include "Space.hpp"
#include "Item.hpp"

class Game
{
private:
    int time = 120;
    int wallet = 200;
    Space* here{nullptr};


public:
    Game();
    ~Game();
    void moveNorth();
    void moveEast();
    void moveSouth();
    void moveWest();
    void play();
};


#endif //INC_162_FINAL_PROJECT_GAME_HPP
