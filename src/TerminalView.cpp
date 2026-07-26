#include "TerminalView.h"
#include "GameTypes.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

namespace Color
{
    const string RESET     = "\033[0m";
    const string Green     = "\033[32m";
    const string Brown     = "\033[38;5;94m";
    const string DarkBlue  = "\033[34m";
    const string Purple    = "\033[35m";
    const string Gray      = "\033[90m";
    const string LightBlue = "\033[96m";
    const string Yellow    = "\033[93m";
}

const map<int, Point> TerminalView::nodeCoordinates =
{
    {0, {14, 3}}, {1, {22, 2}}, {2, {28, 5}}, {3, {35, 6}},
    {4, {43, 7}}, {5, {40, 2}}, {6, {48, 5}}, 
    {7, {53, 2}}, {8, {58, 5}}, {9, {60, 2}},
    {10, {10, 7}}, {11, {16, 8}}, {12, {22, 10}}, {13, {36, 10}}, 
    {14, {48, 9}}, {15, {57, 10}}, {16, {59, 7}}, {17, {64, 9}},
    {18, {9, 12}}, {19, {16, 13}}, {20, {31, 13}}, 
    {21, {12, 15}}, {22, {20, 15}}, {23, {40, 14}},
    {24, {47, 15}}, {25, {56, 16}}, {26, {66, 13}}, 
    {27, {20, 18}}, {28, {28, 17}}, {29, {35, 18}},
    {30, {43, 19}}, {31, {60, 19}}
};

const map<ZoneTypes, string> zoneColorMap =
{
    {ZoneTypes::LightBlue, Color::LightBlue}, {ZoneTypes::Brown, Color::Brown},
    {ZoneTypes::Yellow, Color::Yellow},       {ZoneTypes::Green, Color::Green},
    {ZoneTypes::DarkBlue, Color::DarkBlue},   {ZoneTypes::Purple, Color::Purple},
    {ZoneTypes::Gray, Color::Gray}
};

TerminalView::TerminalView(const Map& m, const Board& b) : map(m), board(b) {}

void TerminalView::display() const
{
    cout << "=============== ASCII MAP ===============\n";
    displayAsciiMap();
    cout << "Space with * is Secret Passage\n";
    cout << "=========================================\n" << endl;
}

void TerminalView::displayAsciiMap() const
{
    vector<string> canvas(MAP_HEIGHT, string(MAP_WIDTH, ' '));
    canvas[0] = "+" + string(MAP_WIDTH - 2, '-') + "+";
    for (int i = 1; i < MAP_HEIGHT - 1; ++i)
    {
        canvas[i][0] = '|';
        canvas[i][MAP_WIDTH - 1] = '|';
    }
    canvas[MAP_HEIGHT - 1] = "+" + string(MAP_WIDTH - 2, '-') + "+";

    set<pair<int, int>> drawn_edges;
    for (int u_id = 0; u_id < 32; ++u_id)
    {
        for (int v_id : map.GetAdjacents(u_id))
        {
            int u = min(u_id, v_id);
            int v = max(u_id, v_id);
            if (drawn_edges.insert({u, v}).second)
            {
                drawLine(canvas, nodeCoordinates.at(u), nodeCoordinates.at(v));
            }
        }
    }

    std::map<pair<int, int>, int> nodeStart;

    for (const auto& p : nodeCoordinates)
    {
        nodeStart[{p.second.x - 2, p.second.y}] = p.first;
    }

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; )
        {
            auto it = nodeStart.find({x, y});
            if (it == nodeStart.end())
            {
                cout << canvas[y][x];
                x++;
                continue;
            }

            int id = it->second;
            const Space& space = map.GetSpace(id);
            const auto& zones = space.GetZones();

            auto getColor = [&](ZoneTypes z)
            {
                return zoneColorMap.count(z) ? zoneColorMap.at(z) : Color::RESET;
            };

            string num = (id < 10) ? "0" + to_string(id) : to_string(id);
            string heroSymbol = board.IsOccupied(id) ? GetHeroSymbol(board.GetOccupiedHeroId(id)) : "";

            string c0 = zones.size() > 0 ? getColor(zones[0]) : Color::RESET;
            string c1 = zones.size() > 1 ? getColor(zones[1]) : c0;
            string c2 = zones.size() > 2 ? getColor(zones[2]) : c1;

            if (zones.empty())
            {
                cout << "[" << num << heroSymbol << "]";
            }
            else
            {
                cout<< c0 << "[" << c1 << num[0] << c2 << num[1] << (heroSymbol.empty() ? "" : Color::RESET + heroSymbol + c0) << "]" << Color::RESET;
            }

            if (space.IsSecretPassage())
            {
                cout << "*";
            }

            int printedLen = 4 + heroSymbol.length() + (space.IsSecretPassage() ? 1 : 0);
            x += printedLen;
        }
        cout << '\n';
    }
}

string TerminalView::GetHeroSymbol(int heroId) const
{
    if (heroId == 1) return "D"; //Dracula
    if (heroId == 5) return "H"; //Holmes
    if (heroId == 6) return "W"; //Watson
    if (heroId >= 2 && heroId <= 4) return "S";
    return " ";
}

void TerminalView::drawLine(vector<string>& canvas, Point p1, Point p2) const
{
    int x1 = p1.x, y1 = p1.y;
    int x2 = p2.x, y2 = p2.y;

    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;

    while (true)
    {
        if (!(x1 == p1.x && y1 == p1.y) && !(x1 == x2 && y1 == y2))
        {
            if (x1 > 0 && x1 < MAP_WIDTH - 1 && y1 > 0 && y1 < MAP_HEIGHT - 1)
            {
                if (canvas[y1][x1] == ' ') canvas[y1][x1] = '.';
            }
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 >= dy)
            { err += dy; x1 += sx; }

        if (e2 <= dx)
            { err += dx; y1 += sy; }
    }
}