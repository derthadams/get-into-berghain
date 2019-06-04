//
// Created by Derth Adams on 2019-06-03.
//

#include "Store.hpp"

Store::Store(std::string name) : Space::Space(name)
{
    type = store;
}

std::string Store::getClerkName()
{
    return clerkName;
}

std::string Store::getClerkDescription()
{
    return clerkDescription;
}

Compass Store::scene(int time, int& wallet, Outfit* outfit)
{

}