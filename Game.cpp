//
// Created by Derth Adams on 2019-06-03.
//

#include <iostream>
#include <fstream>
#include <valarray>
#include "Game.hpp"
#include "Club.hpp"
#include "Street.hpp"
#include "Store.hpp"
#include "getMenuChoice.hpp"

Game::Game()
{
    Space* temp = nullptr;
    Space* last = nullptr;

    here = loadClub("berghain.txt");
    home = here;

    temp = loadStreet("warschauer.txt");
    here->setWest(temp);
    here->getWest()->setEast(here);
    walkWest();

    temp = loadStore("darkstore.txt");
    here->setNorth(temp);
    here->getNorth()->setSouth(here);

    temp = loadStore("savagewear.txt");
    here->setWest(temp);
    here->getWest()->setEast(here);

    temp = loadStreet("kreuzberg.txt");
    here->setSouth(temp);
    here->getSouth()->setNorth(here);
    walkSouth();

    temp = loadStore("slacks.txt");
    here->setSouth(temp);
    here->getSouth()->setNorth(here);

    temp = loadStore("pinkcadillac.txt");
    here->setWest(temp);
    here->getWest()->setEast(here);
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

void Game::driveNorth()
{
    if (here->getNorth())
    {
        time += SHORT_TIME_STEP;
        here = here->getNorth();
    }
}

void Game::driveSouth()
{
    if (here->getSouth())
    {
        time += SHORT_TIME_STEP;
        here = here->getSouth();
    }
}

void Game::playTest()
{
    int choice = 0;
    logLine();
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
        here->scene(time, wallet, &outfit);
//        std::cout << "Current location: " << here->getName() << "\n";
        choice = getMenuChoice("Choose one of these options:\n"
                               "1. Move North\n"
                               "2. Move East\n"
                               "3. Move South\n"
                               "4. Move West\n"
                               "5. Exit\n", 1, 5);
    }
}

void Game::start()
{
    std::cout << "\n";
    std::cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*\n";
    std::cout << "*_*  GET INTO BERGHAIN  *_*\n";
    std::cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n";

    int choice = getMenuChoice("1. Play Game\n2. Quit", 1, 2);
    while (choice !=2)
    {
        play();
        choice = getMenuChoice("1. Play Again\n2. Quit", 1, 2);
    }

}

void Game::play()
{
    NextMove next;
    while (true)
    {
        logLine();
        next = here->scene(time, wallet, &outfit);
        switch (next)
        {
            case North:
            {
                walkNorth();
                break;
            }
            case East:
            {
                walkEast();
                break;
            }
            case South:
            {
                walkSouth();
                break;
            }
            case West:
            {
                walkWest();
                break;
            }
            case DriveNorth:
            {
                driveNorth();
                wallet -= 10;
                break;
            }
            case DriveSouth:
            {
                driveSouth();
                wallet -= 10;
                break;
            }
            case Exit:
            {
                return;
            }
            case Home:
            {
                here = home;
            }
        }
    }
}

void Game::logLine()
{
    std::cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n";
    std::cout << "Time:      " << 19 + (time / 60) << ":";
    if (time % 60 < 10)
    {
        std::cout << "0";
    }
    std::cout << (time % 60);
    if (time >= 0 && time <=120)
    {
        std::cout  << " (" << TIME_LIMIT - time
                  << " minutes left)\n";
    }
    else
    {
        std::cout <<
            " (Your time is up)" << "\n";
    }
    std::cout << "Place:     " << here->getName() << "\n"
              << "Cash left: \u20AC" << wallet << "\n\n";
}

Space* Game::loadStore(std::string filename)
{
    std::string name,
                introText,
                altIntroText,
                clerkName,
                clerkDesc,
                type;
    int category,
        price;
    std::valarray<int> styles = {0,0,0,0};
    Space* tempStore;

    std::ifstream inputFile(filename);

    std::getline(inputFile, name, '$');
    std::getline(inputFile, introText, '$');
    introText.erase(introText.begin());
    std::getline(inputFile, altIntroText, '$');
    altIntroText.erase(altIntroText.begin());
    std::getline(inputFile, clerkName, '$');
    clerkName.erase(std::remove(clerkName.begin(), clerkName.end(), '\n'),
                    clerkName.end());
    std::getline(inputFile, clerkDesc, '$');


    tempStore = new Store(name, introText,altIntroText, clerkName, clerkDesc);

    while (!inputFile.eof())
    {
        std::getline(inputFile, name, '$');
        name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
        std::getline(inputFile, type, '$');
        type.erase(std::remove(type.begin(), type.end(), '\n'), type.end());
        inputFile >> category;
        inputFile >> price;
        inputFile >> styles[0];
        inputFile >> styles[1];
        inputFile >> styles[2];
        inputFile >> styles[3];

        Item* tempItem = new Item(name, type, category, price, styles);
        tempStore->addItem(tempItem);
        tempItem = nullptr;
//        std::cin.ignore();
    }
    return tempStore;
}

Space* Game::loadClub(std::string filename)
{
    std::string name,
                introText,
                altIntroText,
                incompleteOutfitText,
                loseText,
                winText;
    Space* tempClub;

    std::ifstream inputFile(filename);

    std::getline(inputFile, name, '$');
    std::getline(inputFile, introText, '$');
    introText.erase(introText.begin());
    std::getline(inputFile, altIntroText, '$');
    altIntroText.erase(altIntroText.begin());
    std::getline(inputFile, incompleteOutfitText, '$');
    incompleteOutfitText.erase(incompleteOutfitText.begin());
    std::getline(inputFile, loseText, '$');
    loseText.erase(loseText.begin());
    std::getline(inputFile, winText, '$');
    winText.erase(winText.begin());

    tempClub = new Club (name, introText, altIntroText, incompleteOutfitText,
            loseText, winText);
    return tempClub;
}

Space* Game::loadStreet(std::string filename)
{
    std::string name,
                introText,
                altIntroText;
    Space* tempStreet;

    std::ifstream inputFile(filename);

    std::getline(inputFile, name, '$');
    std::getline(inputFile, introText, '$');
    introText.erase(introText.begin());
    std::getline(inputFile, altIntroText, '$');
    altIntroText.erase(altIntroText.begin());

    tempStreet = new Street (name, introText, altIntroText);
    return tempStreet;
}