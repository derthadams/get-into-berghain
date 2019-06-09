/******************************************************************************
**  Program name:  main.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Main file for the "Get Into Berghain" game. Instantiates the
**                 Game class and starts the game using Game::start().
*******************************************************************************/

#include <iostream>
#include "Game.hpp"
#include "AsciiArt.hpp"
#include "getMenuChoice.hpp"

int main()
{
    std::cout << SPLASH_SCREEN;
    std::cout << TOP_DIVIDER;

    int choice = getMenuChoice(PAD05 + "1. Play Game\n" + PAD05 + "2. Quit\n"
                               + BOT_DIVIDER, 1, 2);
    while (choice !=2)
    {
        Game fashiongame;
        fashiongame.play();
        std::cout << SPLASH_SCREEN;
        std::cout << TOP_DIVIDER;
        choice = getMenuChoice(PAD05 + "1. Play Again\n" + PAD05 + "2. Quit\n"
                               + BOT_DIVIDER, 1, 2);
    }

}