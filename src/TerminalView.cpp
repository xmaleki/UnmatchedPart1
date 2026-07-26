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
