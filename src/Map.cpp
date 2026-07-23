#include "Map.h"
#include "Space.h"
#include <iostream>
#include <algorithm>

using namespace std;

Map::Map() = default;

void Map::AddEdge(int Space1, int Space2)
{
    for(int node : Adjacent[Space1])
    {
        if(node == Space2)
            return;
    }

    Adjacent[Space1].push_back(Space2);
    Adjacent[Space2].push_back(Space1);

}


void Map::InitializeSpaces()
{
    Spaces.reserve(32);

    for(int i = 0; i < 32; i++)
    {
        Spaces.push_back(Space(i));
    }
}


void Map::InitializeZones()
{
    Spaces[0].AddZone(ZoneTypes::LightBlue);
    Spaces[1].AddZone(ZoneTypes::LightBlue);
    Spaces[2].AddZone(ZoneTypes::LightBlue);
    Spaces[2].AddZone(ZoneTypes::Brown);
    Spaces[3].AddZone(ZoneTypes::Brown);
    Spaces[4].AddZone(ZoneTypes::Brown);
    Spaces[5].AddZone(ZoneTypes::Brown);
    Spaces[6].AddZone(ZoneTypes::Brown);
    Spaces[6].AddZone(ZoneTypes::Green);
    Spaces[6].AddZone(ZoneTypes::Yellow);
    Spaces[7].AddZone(ZoneTypes::Yellow);
    Spaces[8].AddZone(ZoneTypes::Yellow);
    Spaces[9].AddZone(ZoneTypes::Yellow);
    Spaces[10].AddZone(ZoneTypes::LightBlue);
    Spaces[11].AddZone(ZoneTypes::LightBlue);
    Spaces[12].AddZone(ZoneTypes::LightBlue);
    Spaces[12].AddZone(ZoneTypes::DarkBlue);
    Spaces[13].AddZone(ZoneTypes::Green);
    Spaces[14].AddZone(ZoneTypes::Green);
    Spaces[14].AddZone(ZoneTypes::Purple);
    Spaces[15].AddZone(ZoneTypes::Purple);
    Spaces[16].AddZone(ZoneTypes::Purple);
    Spaces[17].AddZone(ZoneTypes::Purple);
    Spaces[18].AddZone(ZoneTypes::DarkBlue);
    Spaces[19].AddZone(ZoneTypes::DarkBlue);
    Spaces[20].AddZone(ZoneTypes::Green);
    Spaces[21].AddZone(ZoneTypes::DarkBlue);
    Spaces[21].AddZone(ZoneTypes::Gray);
    Spaces[22].AddZone(ZoneTypes::DarkBlue);
    Spaces[22].AddZone(ZoneTypes::Green);
    Spaces[23].AddZone(ZoneTypes::Green);
    Spaces[23].AddZone(ZoneTypes::Gray);
    Spaces[24].AddZone(ZoneTypes::Gray);
    Spaces[25].AddZone(ZoneTypes::Gray);
    Spaces[26].AddZone(ZoneTypes::Purple);
    Spaces[26].AddZone(ZoneTypes::Gray);
    Spaces[27].AddZone(ZoneTypes::Gray);
    Spaces[28].AddZone(ZoneTypes::Gray);
    Spaces[29].AddZone(ZoneTypes::Gray);
    Spaces[30].AddZone(ZoneTypes::Gray);
    Spaces[31].AddZone(ZoneTypes::Gray);
}


void Map::InitializeSecretPassage()
{
    Spaces[0].SetSecretPassage(true);
    secretpass.push_back(0);
    Spaces[9].SetSecretPassage(true);
    secretpass.push_back(9);
    Spaces[13].SetSecretPassage(true);
    secretpass.push_back(13);
    Spaces[27].SetSecretPassage(true);
    secretpass.push_back(27);
}