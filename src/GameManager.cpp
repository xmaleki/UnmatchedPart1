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


void GameManager::InitializeHeroesPositions()
{
    cout<<"==========================================\n";
    cout<<"Initialize Heroes Positions\n";
    cout<<"==========================================\n";
    cout<<"\nThe younger player ["<<player1->GetName()<<"] should choice hero.";
    cout<<"\n1. Space 15\n2. Space 2\nEnter your choice: ";
    int choice;
    cin>>choice;
    while(choice < 1 || choice > 2)
    {
        cout<<"Invalid choice.\nEnter your choice: ";
        cin>>choice;
    }

    int PositionSpace1 = (choice == 1) ? 15 : 2;
    int PositionSpace2 = (choice == 1) ? 2 : 15;
    
    board->SetHeroLocation(player1->GetHeroId(), PositionSpace1);
    //player1->GetHero()->SetLocation(PositionSpace1);

    InitializeSidekicksPositions(player1.get(), PositionSpace1);

    board->SetHeroLocation(player2->GetHeroId(), PositionSpace2);
    //player2->GetHero()->SetLocation(PositionSpace2);

    InitializeSidekicksPositions(player2.get(), PositionSpace2);

    cout<<"The younger player ["<<player1->GetName()<<"] placed in space "<<PositionSpace1<<endl;
    cout<<"The other player placed in space "<<PositionSpace2<<endl;
}


void GameManager::InitializeSidekicksPositions(Player* player, int HeroSpace)
{
    vector<int> SpacesWithSameZones = GameMap->GetSpeacesWithSameZones(HeroSpace);
    vector<int> AvailableSpaces;

    for(int space : SpacesWithSameZones)
    {
        if(space != HeroSpace && !board->IsOccupied(space))
        {
            AvailableSpaces.push_back(space);
        }
    }

    cout<<"\nAvailable spaces for sidekick:\n";
    int counter = 1;

    for(int space : AvailableSpaces)
    {
        cout<<counter<<") Space "<<space<<"\t";
        counter++;

        if(counter % 6 == 0)
            cout<<endl;
    }

    //if(AvailableSpaces.size() < SIDEKISK)

    HeroesTeam team = player->GetHero()->GetTeam();
    int choice;

    if(AvailableSpaces.empty())
    {
        cout<<"No available spaces for sidekicks in this zone!\n";
        return;
    }

    if(team == HeroesTeam::DRACULA)
    {
        for(int i = 1; i <= 3; i++)
        {
            if(AvailableSpaces.empty())
            {
                cout<<"No more available spaces left for sisters.\n";
            }

            int SideKickId = i + 1;
            cout<<"\nPlease choice sister number "<<i<<" location: ";
            cin>>choice;

            if(choice >= 1 && choice <= AvailableSpaces.size())
            {
                board->SetHeroLocation(SideKickId, AvailableSpaces[choice - 1]);
                cout<<"Sister number "<<i<<" placed in "<<AvailableSpaces[choice - 1]<<endl;
                AvailableSpaces.erase(AvailableSpaces.begin() + choice - 1);
            }
            else
            {
                cout<<"Invalid choose. try again.\n";
                i--;
            }

            counter = 1;
            for(int space : AvailableSpaces)
            {
                cout<<counter<<") Space "<<space<<"\t";
                counter++;
            }

            //cout<<"If you want to exit: ";
        }

    }
    else
    {
        while(true)
        {
            if(AvailableSpaces.empty())
            {
                cout<<"No more available spaces left for Watson.\n";
            }

            cout<<"\nPlease enter location of Doctor Watson: ";
            cin>>choice;
            
            if(choice >= 1 && choice <= AvailableSpaces.size())
            {
                board->SetHeroLocation(6, AvailableSpaces[choice - 1]);
                cout<<"Doctor Watson placed in "<<AvailableSpaces[choice - 1]<<".\n";
                AvailableSpaces.erase(AvailableSpaces.begin() + choice - 1);
                break;
            }
            else
            {
                cout<<"Invalid choice.";
                continue;
            }
        }
    }


}
