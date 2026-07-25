#pragma once
#include <vector>
#include "Map.h"
#include "GameTypes.h"

class Board;

class Movement
{
    private:
        const Map& map;
        const Board& board;
    public:
        Movement(const Map& map, const Board& board);
        vector<int> GetAvailableMove(int, int) const;
};