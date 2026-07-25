#include <map>
#include <vector>
#include "GameTypes.h"
#include "Board.h" 
#include <iostream>

using namespace std;

Board::Board(const std::vector<Hero *> &Heroes)
{
    for(const auto&hero : Heroes)
    {
        if(hero)
        {
            HeroesById[hero->GetId()] = hero;
        }
    }
}

