/******************************************************************************
**  Program name:  Game.cpp
**  Author:        Derth Adams
**  Date:          June 11, 2019
**  Description:   Implementation file for the Game class, which implements the
**                 higher-level game logic for the "Get Into Berghain" game.
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <valarray>
#include "Game.hpp"
#include "Club.hpp"
#include "Street.hpp"
#include "Store.hpp"
#include "getMenuChoice.hpp"
//#include "Constants.hpp"

/******************************************************************************
** Function name: Game()
** Description:   Constructor for the Game class. Instantiates all the Space
**                objects, loads their contents from their data files using
**                the load functions, and links them together.
******************************************************************************/

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

/******************************************************************************
** Function name: ~Game()
** Description:   Destructor for the Game class. Deletes the Space pointed to
**                by the "here" pointer, which sets of a cascade of deletions
**                implemented by each Space's destructor.
******************************************************************************/

Game::~Game()
{
    if (here)
    {
        delete here;
        here = nullptr;
    }
    home = nullptr;
}

/******************************************************************************
** Function name: walkNorth()
** Description:   Moves the "here" pointer to the Space to the north and
**                advances the time counter the appropriate amount - a shorter
**                amount of time if you're going between a street and a store,
**                and a longer amount of time if you're traveling between
**                neighborhoods.
******************************************************************************/

void Game::walkNorth()
{
    if (here->getNorth())
    {
        if (here->getType() == street && here->getNorth()->getType() == street)
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

/******************************************************************************
** Function name: walkEast()
** Description:   Moves the "here" pointer to the Space to the east and
**                advances the time counter the appropriate amount.
******************************************************************************/

void Game::walkEast()
{
    if (here->getEast())
    {
        time += SHORT_TIME_STEP;
        here = here->getEast();
    }
}

/******************************************************************************
** Function name: walkSouth()
** Description:   Moves the "here" pointer to the Space to the south and
**                advances the time counter the appropriate amount - a shorter
**                amount of time if you're going between a street and a store,
**                and a longer amount of time if you're traveling between
**                neighborhoods.
******************************************************************************/

void Game::walkSouth()
{
    if (here->getSouth())
    {
        if (here->getType() == street && here->getSouth()->getType() == street)
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

/******************************************************************************
** Function name: walkWest()
** Description:   Moves the "here" pointer to the Space to the west and
**                advances the time counter the appropriate amount.
******************************************************************************/

void Game::walkWest()
{
    if (here->getWest())
    {
        time += SHORT_TIME_STEP;
        here = here->getWest();
    }
}

/******************************************************************************
** Function name: driveNorth()
** Description:   Moves the "here" pointer to the Space to the north,
**                advances the time counter the appropriate amount, and
**                deducts money from the player's wallet for cab fare.
******************************************************************************/

void Game::driveNorth()
{
    if (here->getNorth())
    {
        time += SHORT_TIME_STEP;
        wallet -= CAR_COST;
        here = here->getNorth();
    }
}

/******************************************************************************
** Function name: driveSouth()
** Description:   Moves the "here" pointer to the Space to the south and
**                advances the time counter the appropriate amount, and
**                deducts money from the player's wallet for cab fare.
******************************************************************************/

void Game::driveSouth()
{
    if (here->getSouth())
    {
        time += SHORT_TIME_STEP;
        wallet -= CAR_COST;
        here = here->getSouth();
    }
}

/******************************************************************************
** Function name: start()
** Description:   Main control loop for the game - called from main().
**                Displays game title, asks user if they want to play,
**                starts the game by calling play(), asks if user wants to
**                play again.
******************************************************************************/

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

/******************************************************************************
** Function name: play()
** Description:   Controls gameplay for one iteration of the game. Displays
**                the logline using logLine(), gives control over to the
**                current Space object using Space::scene(), which returns
**                the player's next move as a NextMove enum. Moves the "here"
**                pointer to the next Space using one of the "walk" or "drive"
**                functions, returns back to start() if Space::scene()
**                returns "Exit".
******************************************************************************/

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
                break;
            }
            case DriveSouth:
            {
                driveSouth();
                break;
            }
            case Exit:
            {
                return;
            }
            case Home:
            {
                time += SHORT_TIME_STEP;
                here = home;
            }
        }
    }
}

/******************************************************************************
** Function name: logline()
** Description:   Displays a status logline indicating the current time,
**                minutes left until all the stores close, the player's
**                current location, and amount of cash left.
******************************************************************************/

void Game::logLine()
{
    std::cout << SEPARATOR;
    std::cout << "Time:      " << START_HOUR + (time / 60) << ":";
    if (time % 60 < 10)
    {
        std::cout << "0";
    }
    std::cout << (time % 60);
    if (time >= 0 && time <= TIME_LIMIT)
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

/******************************************************************************
** Function name: loadStore(string)
** Description:   Loads data about the store as well as attributes of each
**                item in its inventory from a text file. Instantiates a
**                Store object with the data and fills its inventory with
**                dynamically created Item objects. Returns a Space pointer
**                to the new Store object.
******************************************************************************/

Space* Game::loadStore(std::string filename)
{
    std::string name,
                introText,
                altIntroText,
                clerkName,
                clerkDesc,
                type,
                response;
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

    for (int i = 0; i < 6; i++)
    {
        std::getline(inputFile, response, '$');
        response.erase(response.begin());
        dynamic_cast<Store*>(tempStore)->addClerkResponse(response);
    }
    for (int i = 0; i < 6; i++)
    {
        std::getline(inputFile, response, '$');
        response.erase(response.begin());
        dynamic_cast<Store*>(tempStore)->addPascalResponse(response);
    }

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
        dynamic_cast<Store*>(tempStore)->addItem(tempItem);
        tempItem = nullptr;
    }
    return tempStore;
}

/******************************************************************************
** Function name: loadStore(string)
** Description:   Loads data about the club from a text file. Instantiates a
**                Club object with the data and returns a Space pointer
**                to the new Club object.
******************************************************************************/

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

/******************************************************************************
** Function name: loadStreet(string)
** Description:   Loads data about the street from a text file. Instantiates a
**                Street object with the data and returns a Space pointer
**                to the new Street object.
******************************************************************************/

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