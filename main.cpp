/******************************************************************************
**  Program name:  main.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Main file for the "Get Into Berghain" game. Instantiates the
**                 Game class and starts the game using Game::start().
*******************************************************************************/

#include <iostream>
#include "Game.hpp"

int main() {
    Game fashiongame;
    fashiongame.start();
    return 0;
}