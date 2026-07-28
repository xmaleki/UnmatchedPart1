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


void GameManager::ShowHand()
{
    cout<<"Hand "<<CurrentPlayer->GetName()<<" :\n";
    const auto& hand = CurrentPlayer->GetHand();
    for(int i = 0; i < hand.size(); i++)
    {
        cout<<i+1<<". "<<hand[i]->GetName()<<"\t";
    }
}


void GameManager::PlayerTurn()
{
    int ActionsRemaining = 2;

    while(ActionsRemaining > 0)
    {
        TerminalView view(*GameMap, *board);
        view.display();

        cout<<"=========--------- Turn "<<CurrentPlayer->GetName()<<" ---------=========\n";

        CurrentPlayer->GetHero()->SpecialAbility(*board, *GameMap, CurrentPlayer);

        cout<<"Actions left: "<<ActionsRemaining<<"\n";
        cout<<"1. Maneuver (Draw a card + Move)\n";
    
        const auto &hand = CurrentPlayer->GetHand();
        vector<int> PlayableCards;
        auto &sidekicks = CurrentPlayer->GetSideKicks();

        if(!hand.empty())
        {
            cout<<"2. HAND:\n\t";
            int Counter = 1;

            for(int i = 0; i < hand.size(); i++)
            {
                bool playable = false;

                if(CanPlayCard(hand[i].get(), CurrentPlayer->GetHero()))
                    playable = true;

                for(auto& side : sidekicks)
                {
                    if(side->IsDead())
                        continue;

                    if(CanPlayCard(hand[i].get(), side.get()))
                    {
                        playable = true;
                        break;
                    }
                }

                if(playable)
                {
                    PlayableCards.push_back(i);
                    cout<< Counter <<") "<< hand[i]->GetName()<< " [" << hand[i]->ToStringType(hand[i]->GetType()) << "] "
                        << "{Owner: " << hand[i]->ToStringOwner(hand[i]->GetOwner()) << "}\t";

                    Counter++;

                    if((Counter) % 3 == 0)
                        cout<<"\n\t";
                }
            }



            if(PlayableCards.empty())
            {
                cout<<"No playable cards. You can only Maneuver.";
            }
            }
            else
            {
                cout<<"Hand is empty.\n";
            }
            
            cout<<"\n3. End Turn\n";
            cout<<"4. End Game\n";
            
            cout<<"Choice: ";
            int choice;
            cin>>choice;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            switch (choice)
            {
                case 1:
                    cout<<"Maneuver: Draw 1 card.\n";
                    Maneuver(*CurrentPlayer, view);
                    ActionsRemaining--;
                    break;

                case 2:
                    if(PlayableCards.empty())
                    {
                        cout<<"############### No playable cards. ###############\n";
                        // end turn
                        // cout<<"Invalid choice. hand empty.";
                        break;
                    }
                    else
                    {
                        cout<<"Enter card number to play: ";
                        int CardIndex;
                        cin >> CardIndex;
                        while(CardIndex < 0 || CardIndex > PlayableCards.size())
                        {
                            cout<<"Invalid choice. Enter again: ";
                            cin>>CardIndex;
                        }

                        int PlayableCardIndex = PlayableCards[CardIndex - 1];
                        auto& card = hand[PlayableCardIndex];
                        // combat if attack or versatile


                        cout<<"Playing card: "<<card->GetName()<<endl;
                        
                        if(card->GetType() == CardType::Scheme)
                        {
                            SchemeContext schemecontext
                            {
                                CurrentPlayer,
                                CurrentPlayer->GetHero(),
                                *board.get(),
                                *GameMap.get(),
                                *movement.get(),
                                &ActionsRemaining,
                                view,
                                OpponentPlayer
                            };


                            card->ApplyScheme(schemecontext);
                            CurrentPlayer->DiscardCardFromHand(card.get());

                            ActionsRemaining--;
                            
                            if(IsGameOver())
                                exit(0);
                        }
                        else if(card->GetType() == CardType::Attack || card->GetType() == CardType::Versatile)
                        {

                            Hero* attacker = ChooseAttackerForCombat(card.get());
                            Hero* defender = ChooseDefenderForCombat(attacker);

                            view.display();

                            combat->StartCombat(CurrentPlayer,  OpponentPlayer, attacker, defender, card.get());
                            
                            ActionsRemaining--;

                            if(IsGameOver())
                                exit(0);
                        }


                        // play card effect 
                    

                        break;
                    }
                            
                    case 3:
                            cout<<"Ending turn...\n";
                            ActionsRemaining = 0;
                        break;
                    
                    
                    case 4:
                        cout<<"Exit game successfully.\n";
                        exit(0);        

                    default:
                        cout<<"Invalid choice!\n";
                        break;
            }


    }

    if(CurrentPlayer->GetHandSize() > 7)
    {
        cout<<"-----------------------------------------\n";
        cout<<"You have more than 7 cards.\n";
        int counter = -1;

        while(CurrentPlayer->GetHandSize() > 0)
        {
            auto &hand = CurrentPlayer->GetHand();
            cout << "Your hand:\n";

            for(int i = 0; i < hand.size(); ++i)
            {
                cout<<i + 1<<") " <<hand[i]->GetName() <<"\t";

                if((i+1) % 3 == 0)
                    cout<<"\n";
            }

            
            if(CurrentPlayer->GetHandSize() <= 7)
            {
                counter = hand.size() + 1;
                cout<<endl<<counter<<") Stop discard your cards";
            }

            cout<<"\nChoose a card to discard: ";
            int choice;
            cin >> choice;

            while(choice < 1 || choice > hand.size() + 1)
            {
                cout<<"Invalid choice. Enter again: ";
                cin>>choice;
            }

            if(counter != -1 && choice == counter)
                break;

            CurrentPlayer->DiscardCardFromHand(hand[choice - 1].get());

        }

    
    }



}


void GameManager::Run()
{
    GameMap->CreateMap();
    

    StartGame();
    InitializeHeroes();

    vector<Hero*> AllHeroes;
    AllHeroes.push_back(player1->GetHero());
    for(const auto& sidekick: player1->GetSideKicks())
    {
        AllHeroes.push_back(sidekick.get());
    }
    AllHeroes.push_back(player2->GetHero());
    for(const auto& sidekick: player2->GetSideKicks())
    {
        AllHeroes.push_back(sidekick.get());
    }

    board = make_unique<Board>(AllHeroes);
    movement = make_unique<Movement>(*GameMap, *board);
    combat = make_unique<Combat>(*board, *GameMap, *movement);

    
    InitializeHeroesPositions();
    
    cout<<"ttt 1\n";

    for(int i = 0; i < 5; i++)
    {
        auto c1 = player1->GetDeck()->DrawCard(player1->GetHero()->GetTeam());
        if(c1)
            player1->AddCardToHand(move(c1));

        auto c2 = player2->GetDeck()->DrawCard(player2->GetHero()->GetTeam());
        if(c2)
            player2->AddCardToHand(move(c2));
    }

    cout<<"ttt 1\n";
    


    CurrentPlayer = player1.get();
    OpponentPlayer = player2.get();

    while(true)
    {
        PlayerTurn();
        swap(CurrentPlayer, OpponentPlayer);
    }
}

void GameManager::Maneuver(Player &player, TerminalView& view)
{
    cout<<"==========================================\n";
    cout<<"Maneuver\n";
    cout<<"==========================================\n";

    HeroesTeam team = player.GetHero()->GetTeam();
    unique_ptr<Card> card = player.GetDeck()->DrawCard(team);
    auto heroes = player.GetAliveHeroes();

    if(card == nullptr)
    {
        cout<<"All your heroes team take 2 damage.";
        //take damage all hero of team
        for(auto &hero : heroes)
        {
            hero->TakeDamage(2);
        }

        return;
    }

    player.AddCardToHand(move(card));



    char MoveChoice;
    cout<<"Move Hero (Y/N)? ";
    cin >> MoveChoice;

    if(MoveChoice != 'y' && MoveChoice != 'Y')
    {
        return;
    }

    

    if(heroes.empty())
        return;

    view.display();
    cout<<"Availabe hero:\n";

    for(int i = 0; i < heroes.size(); i++)
    {
        cout<< i + 1 << ". " << heroes[i]->GetName() <<" Loc: ["<<board->GetHeroLocation(heroes[i]->GetId())<<"]"<< "\t";
    }

    cout<<"\nChoose a Hero: ";
    int choice;
    cin >> choice;
    
    while(choice < 1 || choice > heroes.size())
    {
        cout<<"Invalid Hero!\nEnter again: ";
        cin >> choice;
    }

    Hero* LiveHero = heroes[choice - 1];


    // Boost system
    int MoveCount = 2;
    cout<<"Do you want to Boost your movement? (Y/N): ";
    char BoostChoice;
    cin>>BoostChoice;

    if(BoostChoice == 'y' || BoostChoice == 'Y')
    {
        auto &hand = player.GetHand();
        
        if(hand.empty())
        {
            cout<<"You have no cards to boost with.\n";
        }
        else
        {
            cout<<"-----------------------------------------------------\n";
            cout<<"Choose a card to discard for Boost:\n";

            for(int i = 0; i < hand.size(); i++)
            {
                cout<<i + 1<<") "<<hand[i]->GetName()<<" [Owner:"<<hand[i]->ToStringOwner(hand[i]->GetOwner())<<"] (Boost :"<<hand[i]->GetBoost()<<")\n";
            }
            cout<<"-----------------------------------------------------\nEnter your choice: ";
            int choice;
            cin>>choice;

            while(choice < 1 || choice > hand.size())
            {
                cout<<"Invalid choice. Enter again: ";
                cin>>choice;
            }

            Card* BoostCard = hand[choice - 1].get();
            MoveCount += BoostCard->GetBoost();
            player.DiscardCardFromHand(BoostCard);

            view.display();
            cout<<"Boost applied! New movement = "<<MoveCount<<"\n";
            
        }

    }

    vector<int> moves = movement->GetAvailableMove(MoveCount, LiveHero->GetId());


    if(moves.empty())
    {
        cout<<"No availabe spaces.\n";
        return;
    }

    cout<<"Availble spaces:\n";
    int counter = 1;
    for(auto &move : moves)
    {
        cout<<counter<<") Space "<<move<<"\t";
        counter++;

        if(counter % 6 == 0)
            cout<<endl;
    }

    cout<<"\nEnter your choice: ";
    int SpaceChoice;
    cin >> SpaceChoice;

    while(SpaceChoice < 1 || SpaceChoice > moves.size())
    {
        cout<< "Invalid choice.\nEnter again: ";
        cin >> SpaceChoice;
    }

    int Destination = moves[SpaceChoice - 1];

    board->SetHeroLocation(LiveHero->GetId(), Destination);
    cout<<LiveHero->GetName()<<" Placed in "<<Destination<<" successfully.\n";

}


bool GameManager::CanPlayCard(const Card* card, Hero* hero)
{
    int heroid = hero->GetId();
    int heroSpace = board->GetHeroLocation(heroid);

    if(card->GetOwner() != CardOwner::Any && card->GetOwner() != hero->GetOwnerType())
        return false;
    /*
    if(card->GetOwner() != CardOwner::Any && hero->IsDead())
        return false;
    */

    if(card->GetType() == CardType::Defence)
        return false;

    if(card->GetType() == CardType::Scheme)
        return true;

    bool isAttackCard = (card->GetType() == CardType::Attack) ||
                         (card->GetType() == CardType::Versatile);
    
    if(!isAttackCard)
        return true;

    AttackType type = hero->GetAttackType();

    if(type == AttackType::MELEE)
    {
        for(int neighbor : GameMap->GetAdjacents(heroSpace))
        {
            if(board->IsOccupiedByEnemy(neighbor, heroid))
                return true;
        }

        return false;
    }

    if(type == AttackType::RANGED)
    {
        const auto& heroZones = GameMap->GetSpace(heroSpace).GetZones();

        for(int space = 0; space < 32; space++)
        {
            if(board->IsOccupiedByEnemy(space, heroid))
            {
                const auto& enemyZones = GameMap->GetSpace(space).GetZones();

                for(auto hz :heroZones)
                    for(auto ez : enemyZones)
                        if(hz == ez)
                            return true;

            }
        }

        return false;
    }

    return false;
}


bool GameManager::IsGameOver()
{
    if(player1->GetHero()->IsDead())
    {
        cout<<endl<<player2->GetName()<<" wins the game!\n";
        return true;
    }

    if(player2->GetHero()->IsDead())
    {
        cout<<endl<<player1->GetName()<<" wins the game!\n";
        return true;
    }

    return false;
}




Hero* GameManager::ChooseAttackerForCombat(Card* card)
{
    vector<Hero*> Attackers;

    for(auto *h : CurrentPlayer->GetAliveHeroes())
    {
        if(CanPlayCard(card, h))
        {
            Attackers.push_back(h);
        }
    }


    if(Attackers.empty())
    {
        cout<<"No valid hero can play this card.\n";
        return nullptr;
    }

    cout<<"Available hero:\n";
    for(int i = 0; i < Attackers.size(); i++)
    {
        cout<<i + 1<<") "<<Attackers[i]->GetName()<<" [HP = "<<Attackers[i]->GetHP()<<"] {Loc: "<<board->GetHeroLocation(Attackers[i]->GetId())<<"}\t";
    }
    cout<<"\nChoose hero: ";
    
    int AttackerChoice;
    cin>>AttackerChoice;

    while(AttackerChoice <= 0 || AttackerChoice > Attackers.size())
    {
        cout<<"Invalid choice. Enter again: ";
        cin>>AttackerChoice;
    }

    return Attackers[AttackerChoice - 1];
}

