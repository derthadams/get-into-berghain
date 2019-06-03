//
// Created by Derth Adams on 2019-06-03.
//

#include <iostream>
#include "Game.hpp"
#include "Club.hpp"
#include "Street.hpp"
#include "Store.hpp"

Game::Game()
{
    Space* temp = nullptr;
    here = new Club("Berghain");
    temp = new Street("Warschauer Strasse");
    here->setWest(temp);
    moveWest();
    temp = new Store("Darkstore");
    here->setNorth(temp);
    temp = new Store("Savage-Wear");
    here->setWest(temp);
    temp = new Street("Kreuzberg");
    here->setSouth(temp);
    moveSouth();
    temp = new Store("The Gap");
    here->setEast(temp);
    temp = new Store("Prada");
    here->setSouth(temp);
    temp = new Store("TJ Maxx");
    here->setWest(temp);
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

void play()
{

}