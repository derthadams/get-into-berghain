//
// Created by Derth Adams on 2019-06-03.
//

#include <iostream>
#include "Game.hpp"
#include "Club.hpp"
#include "Street.hpp"
#include "Store.hpp"
#include "getMenuChoice.hpp"

Game::Game()
{
    Space* temp = nullptr;
    Space* last = nullptr;
    here = new Club("The front of Berghain");
    // Load function for Club
    temp = new Street("Warschauer Strasse");
    here->setWest(temp);
    here->getWest()->setEast(here);
    // Load function for Street
    walkWest();
    temp = new Store("Darkstore");
    here->setNorth(temp);
    here->getNorth()->setSouth(here);
    // Load function for Store
    temp = new Store("Savage-Wear");
    here->setWest(temp);
    here->getWest()->setEast(here);
    // Load function for Store
    temp = new Street("Kreuzberg Strasse");
    here->setSouth(temp);
    here->getSouth()->setNorth(here);
    // Load function for Street
    walkSouth();
    temp = new Store("The Gap");
    here->setEast(temp);
    here->getEast()->setWest(here);
    // Load function for Store
    temp = new Store("Prada");
    here->setSouth(temp);
    here->getSouth()->setNorth(here);
    // Load function for Store
    temp = new Store("TJ Maxx");
    here->setWest(temp);
    here->getWest()->setEast(here);
    // Load function for Store
    walkNorth();
    walkEast();
    temp = nullptr;
    time = 0;
}

Game::~Game()
{
    if (here)
    {
        delete here;
        here = nullptr;
    }
}

void Game::walkNorth()
{
    if (here->getNorth())
    {
        if (here->getName() == "Kreuzberg Strasse")
        {
            time += LONG_TIME_STEP;
        }
        else
        {
            time += SHORT_TIME_STEP;
        }
        here = here->getNorth();
    }
}

void Game::walkEast()
{
    if (here->getEast())
    {
        time += SHORT_TIME_STEP;
        here = here->getEast();
    }
}

void Game::walkSouth()
{
    if (here->getSouth())
    {
        if (here->getName() == "Warschauer Strasse")
        {
            time += LONG_TIME_STEP;
        }
        else
        {
            time += SHORT_TIME_STEP;
        }
        here = here->getSouth();
    }
}

void Game::walkWest()
{
    if (here->getWest())
    {
        time += SHORT_TIME_STEP;
        here = here->getWest();
    }
}

void Game::uberNorth()
{
    if (here->getNorth())
    {
        time += SHORT_TIME_STEP;
        here = here->getNorth();
    }
}

void Game::uberSouth()
{
    if (here->getSouth())
    {
        time += SHORT_TIME_STEP;
        here = here->getSouth();
    }
}

void Game::play()
{
    int choice = 0;
    logLine();
//    std::cout << "Current location: " << here->getName() << "\n";
    choice = getMenuChoice("Choose one of these options:\n"
                           "1. Move North\n"
                           "2. Move East\n"
                           "3. Move South\n"
                           "4. Move West\n"
                           "5. Exit\n", 1, 5);
    while (choice != 5)
    {
        switch(choice)
        {
            case 1:
            {
                walkNorth();
                break;
            }
            case 2:
            {
                walkEast();
                break;
            }
            case 3:
            {
                walkSouth();
                break;
            }
            case 4:
            {
                walkWest();
                break;
            }
        }
        logLine();
        std::cout << "Current location: " << here->getName() << "\n";
        choice = getMenuChoice("Choose one of these options:\n"
                               "1. Move North\n"
                               "2. Move East\n"
                               "3. Move South\n"
                               "4. Move West\n"
                               "5. Exit\n", 1, 5);
    }
}

void Game::logLine()
{
    std::cout << "Time:      " << 19 + (time / 60) << ":";
    if (time % 60 < 10)
    {
        std::cout << "0";
    }
    std::cout << (time % 60);
    if (time > 0)
    {
        std::cout  << " (" << TIME_LIMIT - time
                  << " minutes left)\n";
    }
    else
    {
        std::cout << "\n";
    }
    std::cout << "Place:     " << here->getName() << "\n"
              << "Cash left: \u20AC" << wallet << "\n\n";
}