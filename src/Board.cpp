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

bool Board::IsOccupied(int SpaceId) const
{
    auto it = LocationOfHeroes.find(SpaceId);

    if(it == LocationOfHeroes.end())
        return false;

    int heroid = it->second;
    const Hero* h = GetHeroById(heroid);

    if(h == nullptr || h->IsDead())
    {
        return false;
    }

    return true;
}


int Board::GetOccupiedHeroId(int SpaceId) const
{
    if(IsOccupied(SpaceId))
    {
        return LocationOfHeroes.at(SpaceId);
    }

    return -1;
}
