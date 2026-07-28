#include "GameManager.h"
#include "Dracula.h"
#include "Sherlock.h"
#include "GameTypes.h"
#include "Sister.h"
#include "Watson.h"
#include "Combat.h"
#include <iostream>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

GameManager::GameManager()
{
    GameMap = std::make_unique<Map>();
}

void GameManager::StartGame()
{
    cout<<"===================== Unmatched =====================\n";

    int Year1, Month1, Day1;
    int Year2, Month2, Day2;
    string NameOfPlayer1, NameOfPlayer2;


    cout<<"Enter name of player number 1 : ";
    cin>>NameOfPlayer1;

    cout<<"Enter age of player number 1"<<endl;
    cout<<"Year: ";
    cin>>Year1;
    cout<<"Month: ";
    cin>>Month1;
    cout<<"Day: ";
    cin>>Day1;

    cout<<"Enter name of player number 2 : ";
    cin>>NameOfPlayer2;

    cout<<"\nEnter age of player number 2:\n";
    cout<<"Year: ";
    cin>>Year2;
    cout<<"Month: ";
    cin>>Month2;
    cout<<"Day: ";
    cin>>Day2;


    // mishe operator overload kard. badan age shod in karo mikonam.
    if(Year1 > Year2)
    {
        player1 = make_unique<Player>(NameOfPlayer1 ,Year1, Month1, Day1);
        player2 = make_unique<Player>(NameOfPlayer2 ,Year2, Month2, Day2);
    }
    else if(Year1 < Year2)
    {
        player1 = make_unique<Player>(NameOfPlayer2 ,Year2, Month2, Day2);
        player2 = make_unique<Player>(NameOfPlayer1 ,Year1, Month1, Day1);
    }
    else
    {
        if(Month1 > Month2)
        {
            player1 = make_unique<Player>(NameOfPlayer1 ,Year1, Month1, Day1);
            player2 = make_unique<Player>(NameOfPlayer2 ,Year2, Month2, Day2);
        }
        else if(Month1 < Month2)
        {
            player1 = make_unique<Player>(NameOfPlayer2 ,Year2, Month2, Day2);
            player2 = make_unique<Player>(NameOfPlayer1 ,Year1, Month1, Day1);
        }
        else
        {
            if(Day1 >= Day2)
            {
                player1 = make_unique<Player>(NameOfPlayer1 ,Year1, Month1, Day1);
                player2 = make_unique<Player>(NameOfPlayer2 ,Year2, Month2, Day2);
            }
            else if(Day2 > Day1)
            {
                player1 = make_unique<Player>(NameOfPlayer2 ,Year2, Month2, Day2);
                player2 = make_unique<Player>(NameOfPlayer1 ,Year1, Month1, Day1);
            }
        }
    }
    
}

