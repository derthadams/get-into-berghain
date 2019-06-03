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
    here = new Club("Berghain");
    temp = new Street("Warschauer Strasse");
    here->setWest(temp);
    here->getWest()->setEast(here);
    moveWest();
    temp = new Store("Darkstore");
    here->setNorth(temp);
    here->getNorth()->setSouth(here);
    temp = new Store("Savage-Wear");
    here->setWest(temp);
    here->getWest()->setEast(here);
    temp = new Street("Kreuzberg");
    here->setSouth(temp);
    here->getSouth()->setNorth(here);
    moveSouth();
    temp = new Store("The Gap");
    here->setEast(temp);
    here->getEast()->setWest(here);
    temp = new Store("Prada");
    here->setSouth(temp);
    here->getSouth()->setNorth(here);
    temp = new Store("TJ Maxx");
    here->setWest(temp);
    here->getWest()->setEast(here);
    moveNorth();
    moveEast();
}

Game::~Game()
{

}

void Game::moveNorth()
{
    here = here->getNorth();
}

void Game::moveEast()
{
    here = here->getEast();
}

void Game::moveSouth()
{
    here = here->getSouth();
}

void Game::moveWest()
{
    here = here->getWest();
}

void Game::play()
{
    int choice = 0;
    std::cout << "Current location: " << here->getName() << "\n";
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
                moveNorth();
                break;
            }
            case 2:
            {
                moveEast();
                break;
            }
            case 3:
            {
                moveSouth();
                break;
            }
            case 4:
            {
                moveWest();
                break;
            }
        }
        std::cout << "Current location: " << here->getName() << "\n";
        choice = getMenuChoice("Choose one of these options:\n"
                               "1. Move North\n"
                               "2. Move East\n"
                               "3. Move South\n"
                               "4. Move West\n"
                               "5. Exit\n", 1, 5);
    }
}