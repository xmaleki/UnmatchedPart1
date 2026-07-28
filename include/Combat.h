#pragma once
#include "Hero.h"
#include "Card.h"
#include "Player.h"
#include "Board.h"
#include "Map.h"
#include <vector>

class Combat
{
    private:
        Board& board;
        Map& map;
        Movement& movement;

    public:
        Combat(Board &b, Map& mc, Movement & );
        void StartCombat(Player*, Player*, Hero*, Hero*, Card*);
        vector<Hero*> GetValidTargets(Hero*);
        Hero* ChooseTarget(Hero*);
};