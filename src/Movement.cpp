#include "Movement.h"
#include "Board.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

Movement::Movement(const Map& inmap, const Board& inboard): map(inmap), board(inboard){} 

vector<int> Movement::GetAvailableMove(int MoveCount, int Heroid) const
{
    queue<int> Queue;
    vector<int> Distance(32 , -1); // fasele har noghte ta shoro
    vector<int> Result;

    int StartSpace = board.GetHeroLocation(Heroid);

    Distance[StartSpace] = 0;
    Queue.push(StartSpace);

    while(!Queue.empty())
    {
        int Current = Queue.front();
        Queue.pop();

        const vector<int>& neighbors = map.GetAdjacents(Current);
        
        for(int neighbor : neighbors)
        {
            if(Distance[neighbor] == -1)
            {
                // takmil mikonim
                if(board.IsOccupiedByEnemy(neighbor, Heroid))
                {
                    continue;
                }

                if(board.IsOccupiedByTeammate(neighbor, Heroid))
                {
                    if(Distance[Current] + 1 < MoveCount)
                    {
                        Distance[neighbor] = Distance[Current] + 1;
                        Queue.push(neighbor);
                    }

                    continue;
                }



                Distance[neighbor] = Distance[Current] + 1;

                if(Distance[neighbor] <= MoveCount)
                {
                    Queue.push(neighbor);
                }
            }
        }


        if(map.GetSpace(Current).IsSecretPassage())
        {   
            const vector<int>& Passages = map.GetSecretPassages();           
            for(int pas : Passages)
            {
                if(pas == Current) continue;

                if(Distance[pas] == -1 && !board.IsOccupiedByEnemy(pas, Heroid))
                {
                    if(board.IsOccupiedByTeammate(pas, Heroid))
                    {
                        if(Distance[Current] + 1 < MoveCount)
                        {
                            Distance[pas] = Distance[Current] + 1;
                            Queue.push(pas);
                        }
                        continue;
                    }


                    Distance[pas] = Distance[Current] + 1;
                    
                    if(Distance[pas] <= MoveCount)
                    {
                        Queue.push(pas);
                    }
                }
            }
        }
    }


    for(int i = 0; i < 32; i++)
    {
        if(Distance[i] > 0 && Distance[i] <= MoveCount && !board.IsOccupiedByTeammate(i, Heroid))
        {
            Result.push_back(i);
        }
    }

    return Result;
}
