#pragma once

#include <map>
#include <vector>
#include "GameTypes.h"
#include "Hero.h"

class Board
{
    private:
        std::map<int, int> LocationOfHeroes; // faqat khane haye eshghal shode negahdari mishan. (SpaceId : HeroId)
        std::map<int, Hero*> HeroesById; // HeroId : Hero pointer
        std::map<int, int> HeroPositions; // HeroId : SpaceId
    public:
        Board(const std::vector<Hero *> &Heroes);
        bool IsOccupied(int ) const;
        bool IsOccupiedByEnemy(int, int) const;
        bool IsOccupiedByTeammate(int, int) const;
        int GetOccupiedHeroId(int) const;
        void SetHeroLocation(int, int);
        int GetHeroLocation(int) const;
        Hero* GetHeroById(int) const;
        Hero* GetHeroBySpace(int) const;
        HeroesTeam GetTeamOfHero(int ) const;
        std::vector<int> GetAvailableSpace();
};