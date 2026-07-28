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


void GameManager::InitializeHeroes()
{
    cout<<"The younger player ["<<player1->GetName()<<"] should choose hero first.";
    cout<<"\n1. Dracula\n2. Sherlock\n";
    cout<<'"'<<player1->GetName()<<'"'<<" chose hero: ";
 
    int choice;
    
    while(true)
    {
        cin >> choice;
        if(choice <= 0 || choice > 2)
        {
            cout<<"Invalid choice.\nchoose hero: ";
            continue;
        }
        else
            break;
    }

    std::unique_ptr<Hero> hero1, hero2;
    int Player1HeroId, Player2HeroId;

    if(choice == 1)
    {
        hero1 = std::make_unique<Dracula>("Dracula", 1, HeroesTeam::DRACULA, 13, AttackType::MELEE, 13, CardOwner::Dracula);
        Player1HeroId = 1;
        hero2 = std::make_unique<Sherlock>("Holmes" , 5, HeroesTeam::SHERLOCK, 16, AttackType::MELEE, 16, CardOwner::SherlockHolmes);
        Player2HeroId = 5;

    }
    else
    {
        hero1 = std::make_unique<Sherlock>("Holmes", 5, HeroesTeam::SHERLOCK, 16, AttackType::MELEE, 16, CardOwner::SherlockHolmes);
        Player1HeroId = 5;
        hero2 = std::make_unique<Dracula>("Dracula", 1, HeroesTeam::DRACULA, 13, AttackType::MELEE, 13, CardOwner::Dracula);
        Player2HeroId = 1;
    }

    player1->SetHero(std::move(hero1), Player1HeroId);
    player2->SetHero(std::move(hero2), Player2HeroId);
    player1->InitializeDeck(player1->GetHero()->GetTeam());
    player2->InitializeDeck(player2->GetHero()->GetTeam());
    
    player1->GetDeck()->Shuffle(player1->GetHero()->GetTeam());
    player2->GetDeck()->Shuffle(player2->GetHero()->GetTeam());

    if(player1->GetHero()->GetTeam() == HeroesTeam::DRACULA)
    {
        player1->SetSideKicks(make_unique<Sister>("Sister", 2, HeroesTeam::DRACULA, 1, AttackType::MELEE, 1, CardOwner::Sisters), 2);
        player1->SetSideKicks(make_unique<Sister>("Sister", 3, HeroesTeam::DRACULA, 1, AttackType::MELEE, 1, CardOwner::Sisters), 3);
        player1->SetSideKicks(make_unique<Sister>("Sister", 4, HeroesTeam::DRACULA, 1, AttackType::MELEE, 1, CardOwner::Sisters), 4);
        player2->SetSideKicks(make_unique<Watson>("Watson", 6, HeroesTeam::SHERLOCK, 8, AttackType::RANGED, 8, CardOwner::DrWatson),6);
    }
    else
    {
        player1->SetSideKicks(make_unique<Watson>("Watson", 6, HeroesTeam::SHERLOCK, 8, AttackType::RANGED, 8, CardOwner::DrWatson), 6);
        player2->SetSideKicks(make_unique<Sister>("Sister", 2, HeroesTeam::DRACULA, 1, AttackType::MELEE, 1, CardOwner::Sisters), 2);
        player2->SetSideKicks(make_unique<Sister>("Sister", 3, HeroesTeam::DRACULA, 1, AttackType::MELEE, 1, CardOwner::Sisters), 3);
        player2->SetSideKicks(make_unique<Sister>("Sister", 4, HeroesTeam::DRACULA, 1, AttackType::MELEE, 1, CardOwner::Sisters), 4);
    }

    cout<<"****************** Heroes and Sidekicks initialized successfully. ******************\n";
}
