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



vector<int> Map::GetSpeacesWithSameZones(int id)
{
    vector<int> result;
    
    const auto &TargetZones = Spaces[id].GetZones();

    for(const auto &space : Spaces)
    {
        for(const auto &zone : TargetZones)
        {
            if(space.HasZone(zone))
            {
                result.push_back(space.GetId());
                break;
            }      
        } 
    }

    return result;
}



void Map::CreateMap()
{
    InitializeSpaces();
    InitializeZones();
    InitializeSecretPassage();
    CreateEdges();
}

void Map::CreateEdges()
{
    Adjacent.resize(32);
    AddEdge(0,1);
    AddEdge(0,10);
    AddEdge(10,11);
    AddEdge(10,18);
    AddEdge(18,19);
    AddEdge(18,21);

    AddEdge(21,22);
    AddEdge(21,27);
    AddEdge(27,28);
    AddEdge(28,29);
    AddEdge(1,2);

    AddEdge(12,2);
    AddEdge(12,11);
    AddEdge(12,19);
    AddEdge(22,20);
    AddEdge(20,23);
    AddEdge(23,30);

    AddEdge(23,30);
    AddEdge(24,30);
    AddEdge(13,20);
    AddEdge(13,14);
    AddEdge(2,3);

    AddEdge(4,3);
    AddEdge(5,4);
    AddEdge(5,3);
    AddEdge(5,6);
    AddEdge(4,6);

    AddEdge(7,6);
    AddEdge(8,6);
    AddEdge(7,9);
    AddEdge(14,15);
    AddEdge(14,16);


    AddEdge(17,16);
    AddEdge(15,17);
    AddEdge(17,26);
    AddEdge(31,26);
    AddEdge(25,26);

    AddEdge(25,24);
    AddEdge(25,14);
    AddEdge(24,14);
    AddEdge(23,24);

    AddEdge(29,23);


    AddEdge(7,8);

    AddEdge(25,31);

    AddEdge(29,30);

    AddEdge(14,6);

    AddEdge(8,16);
}
