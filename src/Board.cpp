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


bool Board::IsOccupiedByTeammate(int SpaceId , int MovingHeroId) const
{
    if(!IsOccupied(SpaceId))
        return false;

    int OccupantHeroId = GetOccupiedHeroId(SpaceId);
    
    if(OccupantHeroId == MovingHeroId)
        return false;

    return GetTeamOfHero(OccupantHeroId) == GetTeamOfHero(MovingHeroId);
}

bool Board::IsOccupiedByEnemy(int SpaceId, int MovingHeroId) const
{
    if(!IsOccupied(SpaceId))
        return false;
    
    int OccupantHeroId = GetOccupiedHeroId(SpaceId);

    if(OccupantHeroId == MovingHeroId)
        return false;

    return GetTeamOfHero(OccupantHeroId) != GetTeamOfHero(MovingHeroId);

}


HeroesTeam Board::GetTeamOfHero(int HeroId) const
{
    const Hero* hero = HeroesById.at(HeroId);
    
    if(hero != nullptr)
        return hero->GetTeam();
    else
        return HeroesTeam::WITHOUTTEAM;
}


void Board::SetHeroLocation(int HeroId, int SpaceId)
{
    if(HeroPositions.count(HeroId))
    {
        int old = HeroPositions[HeroId];
        if(LocationOfHeroes.count(old) && LocationOfHeroes[old] == HeroId)
        {
            LocationOfHeroes.erase(old);
        }
    }
    LocationOfHeroes[SpaceId] = HeroId;
    HeroPositions[HeroId] = SpaceId;
}


int Board::GetHeroLocation(int HeroId) const
{
    if(HeroPositions.count(HeroId))
    {
        return HeroPositions.at(HeroId);
    }
    return -1;
}


Hero* Board::GetHeroById(int HeroId) const
{
    auto it = HeroesById.find(HeroId);

    if(it != HeroesById.end())
        return it->second;

    return nullptr;
}   


Hero* Board::GetHeroBySpace(int Space) const
{
    auto it = LocationOfHeroes.find(Space);

    if(it == LocationOfHeroes.end())
        return nullptr;

    return GetHeroById(it->second);
}


vector<int> Board::GetAvailableSpace()
{
    vector<int> Spaces;

    for(int i = 0; i < 32; i++)
    {
        if(!IsOccupied(i))
            Spaces.push_back(i);
    }

    return Spaces;
}
