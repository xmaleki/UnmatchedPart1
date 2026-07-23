#pragma once
#include <vector>
#include <memory>

class Map
{
    private:
        vector<Space> Spaces;
        vector<vector<int>> Adjacent; 
        vector<int> secretpass;
    public:
        Map();
        const Space& GetSpace(int) const;
        void AddEdge(int , int);
        void InitializeSpaces();
        void InitializeZones();
        void InitializeSecretPassage();
        vector<int> GetSpeacesWithSameZones(int);
        void CreateMap();
        void CreateEdges();
        const vector<int>& GetAdjacents(int) const;
        const vector<int>& GetSecretPassages() const;
};