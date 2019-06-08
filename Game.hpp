/******************************************************************************
**  Program name:  Game.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Header file for the Game class, which implements the
**                 higher-level game logic for the "Get Into Berghain" game.
*******************************************************************************/

#ifndef INC_162_FINAL_PROJECT_GAME_HPP
#define INC_162_FINAL_PROJECT_GAME_HPP
#include <array>
#include "Space.hpp"
#include "Item.hpp"
#include "Constants.hpp"

class Game
{
private:

    int time = 0;           // Number of game-minutes elapsed
    int wallet = STARTING_EUROS;       // Number of Euros in the player's wallet
    Outfit outfit;          // Outfit object containing clothing purchases
    Space* here{nullptr};   // Pointer to the Space object the player is
                            // currently in.
    Space* home{nullptr};   // Pointer to the Space object representing
                            // Berghain, the place where the game begins
                            // and ends.
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