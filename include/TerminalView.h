#pragma once

#include "Map.h"
#include "Board.h"
#include <vector>
#include <string>
#include <map>

struct Point
{
    int x, y;
};

class TerminalView 
{
public:
    explicit TerminalView(const Map& , const Board& );
    void display() const;
    int getVisibleLength(const std::string& str) const;
    std::string GetHeroSymbol(int heroId) const;

private:
    const Map& map;
    const Board& board;
    static const std::map<int, Point> nodeCoordinates;
    const int MAP_WIDTH = 78;
    const int MAP_HEIGHT = 22;
    void displayAsciiMap() const;
    void drawLine(std::vector<std::string>& canvas, Point p1, Point p2) const;
    std::string getColoredNodeString(int nodeId) const;
    std::string BuildNodeString(int) const;
};
