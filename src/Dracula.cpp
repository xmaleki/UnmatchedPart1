#include "Dracula.h"
#include "iostream"


void Dracula::SpecialAbility(Board& board, Map& map, Player* CurrentPlayer)
{
    auto adj = map.GetAdjacents(board.GetHeroLocation(this->GetId()));
    vector<Hero*> Targets;

    for(int space : adj)
    {
        if(board.IsOccupied(space))
        {
            Hero* h = board.GetHeroBySpace(space);
            if(h && !h->IsDead())
            {
                Targets.push_back(h);
            }
        }
    }

    if(Targets.empty())
    {
        cout<<"[Dracula Special Ability] No adjacents heroes.\n";
        return;
    }

    cout<<"[Dracula Special Ability] Use dracula's ability (Y/N)? ";
    char choice;
    cin>>choice;

    if(choice !='y' && choice != 'Y')
    {
        cout<<"Dracula special ability didn't execute.\n";
        return;
    }
    
    cout<<"Choose a hero to deal 1 damage:\n";
    for(int i = 0; i < Targets.size(); i++)
    {
        cout<<i + 1<<") "<<Targets[i]->GetName()<<" Loc: ["<<board.GetHeroLocation(Targets[i]->GetId())<<"]"<<"\t";
    }
    
    int TargetChoice;
    cin>>TargetChoice;

    while(TargetChoice < 1 || TargetChoice > Targets.size())
    {
        cout<<"Invalid choice. Enter again: ";
        cin>>TargetChoice;
    }

    Hero* target = Targets[TargetChoice - 1];
    target->TakeDamage(1);

    cout<<"[Dracula Special Ability] "<<target->GetName()<<" takes 1 damage.\n";
    
    auto card = CurrentPlayer->GetDeck()->DrawCard(this->GetTeam());
    if(card)
    {
        CurrentPlayer->AddCardToHand(move(card));
        cout<<"[Dracula Special Ability] Dracula draws 1 card.\n";
    }


}