#include "Card.h"
#include "GameTypes.h"
#include <iostream>
#include <random>
#include <memory>
#include <Deck.h>
#include "Hero.h"
#include <algorithm>
#include "Board.h"
#include "Map.h"
#include "Player.h"
#include "Movement.h"
#include "TerminalView.h"

using namespace std;

Card::Card(const std::string&name, CardType type, int value, int boost,
Timing timing, const std::string& effect, CardOwner owner):Name(name), Type(type), Value(value),
Boost(boost), Time(timing), EffectDescription(effect), Owner(owner)
{}

std::string Card::GetName() const
{
    return Name;
}

CardType Card::GetType() const
{
    return Type;
}

string Card::ToStringType(CardType type) const
{
    switch (type)
    {
    case CardType::Attack:
        return "Attack";
        break;
    case CardType::Defence:
        return "Defence";
        break;
    case CardType::Versatile:
        return "Versatile";
        break;
    case CardType::Scheme:
        return "Scheme";
        break;

    default:
        return "";
        break;
    }
}

int Card::GetValue() const
{
    return Value;
}

int Card::GetBoost() const
{
    return Boost;
}

Timing Card::GetTiming() const
{
    return Time;
}

std::string Card::GetEffect() const
{
    return EffectDescription;
}

CardOwner Card::GetOwner() const
{
    return Owner;
}

string Card::ToStringOwner(CardOwner owner) const
{
    switch (owner)
    {
    case CardOwner::Dracula:
        return "Dracula";
        break;
    
    case CardOwner::DrWatson:
        return "Dr Watson";
        break;

    case CardOwner::SherlockHolmes:
        return "Sherlock Holmes";
        break;
    
    case CardOwner::Sisters:
        return "Sister";
        break;

    case CardOwner::Any:
        return "Any";
        break;

    default:
        return "";
        break;
    }

}

FeedingFrenzy::FeedingFrenzy():Card("Feeding Frenzy", CardType::Attack, 2, 3, Timing::DuringCombat, 
        "DURING COMBAT: This card's value is +1 for each Sister in the same zone as the opposing fighter.", CardOwner::Dracula)
{}


void FeedingFrenzy::ApplyDuringCombat(CombatContext &context)
{
    int TargetSpace = context.board.GetHeroLocation(context.Defender->GetId());
    const auto& TargetZones = context.map.GetSpace(TargetSpace).GetZones();
    int count = 0;

    // khahar ha
    for(const auto& Hero : context.AttackerPlayer->GetAliveHeroes())
    {
        if(Hero->GetName() != "Sister")
            continue;
        if(Hero->IsDead())
            continue;

        int SisterSpace = context.board.GetHeroLocation(Hero->GetId());
        const auto& SisterZones = context.map.GetSpace(SisterSpace).GetZones();

        for(auto tz : TargetZones)
            for(auto sz : SisterZones)
                if(tz == sz)
                    count++;
    }

    context.AttackValue += count;
}


MistForm::MistForm() : Card("Mistform", CardType::Scheme, 0, 2, Timing::Event,
        "Place Dracula in any space. Gain 1 action.", CardOwner::Dracula)
{}

void MistForm::ApplyScheme(SchemeContext& schemecontext)
{   
    schemecontext.terminalview.display();

    auto Available = schemecontext.board.GetAvailableSpace();
    if(Available.empty())
    {
        cout<<"[MistForm] No valid spaces.\n";
        return;
    }

    cout<<"[MistForm] Choose a space to place Dracula\n";
    for(int i = 0; i < Available.size(); i++)
    {
        cout<<i + 1<<") Space"<<Available[i]<<"\t";

        if((i + 1) % 6 == 0)
            cout<<endl;
    }
    
    cout<<"Enter your choice: ";
    int choice;
    while (true)
    {
        cin>>choice;
        if(choice < 1 || choice > Available.size())
        {
            cout<<"[MistForm] Invalid choice.\nEnter again: ";
            cin>>choice;
        }
        else
            break;
    }

    schemecontext.board.SetHeroLocation(schemecontext.hero->GetId(), Available[choice - 1]);
    
    cout<<"[MistForm] Dracula moved to space "<<Available[choice - 1]<<".\n";

    (*schemecontext.ActionsRemain)++;
    cout<<"[MistForm] You gained +1 action.\n";
}

Ambush::Ambush():Card("Ambush", CardType::Attack, 2, 3, Timing::DuringCombat,
        "DURING COMBAT: Your opponent discards 1 random card. Add its BOOST value to this card's attack value.",
        CardOwner::Any)
{}

void Ambush::ApplyDuringCombat(CombatContext &context)
{
    if(context.DefenderPlayer->GetHandSize() == 0)
    {
        cout<<"[Ambush] Opponent has no cards to discard.\n";
        return;
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> RandGen(0, context.DefenderPlayer->GetHandSize() - 1);

    int DefenderRandomCardIndex = RandGen(generator);
    
    Card* RandomCardHand = context.DefenderPlayer->GetCardFromHand(DefenderRandomCardIndex);
    
    cout<<"[Ambush] Random card is "<< RandomCardHand->GetName()<<" and boost value is "<<RandomCardHand->GetBoost()<<"\n";

    context.AttackValue = RandomCardHand->GetBoost() + context.AttackCard->GetValue();

    context.DefenderPlayer->DiscardCardFromHand(RandomCardHand);

    cout<<"[Ambush] The opponent discards a card. The boost value of that card is added to the attack value.\n";
    cout<<"Attack is now "<<context.AttackValue<<".\n";
}


BaptismOfBlood::BaptismOfBlood() : Card("Baptism of Blood", CardType::Scheme, 0, 2, Timing::Event,
        "Recover 2 health. Return a defeated Sister (if any) to any space in Dracula's zone.", CardOwner::Dracula)
{}


void BaptismOfBlood::ApplyScheme(SchemeContext &context)
{
    context.hero->Heal(2);

    vector<Hero*> DeadSisters;

    
    for(auto &sk : context.player->GetSideKicks())
    {
        if(sk->GetName() == "Sister" && sk->IsDead())
        {
            DeadSisters.push_back(sk.get());
        }
    }

    if(DeadSisters.empty())
    {
        cout<<"[Baptism Of Blood] There is no dead sister.\n";
        return;
    }
    
    int schoice = 1;
    if(DeadSisters.size() > 1)
    {
        for(int i = 0; i < DeadSisters.size(); i++)
        {
            cout<<i + 1<<") "<<DeadSisters[i]->GetName()<<"\t";
        }

        cout<<"\nEnter choice: ";
        cin>>schoice;

        while(schoice < 1 || schoice > DeadSisters.size())
        {
            cout<<"Invalid choice. Enter again: ";
            cin>>schoice;
        }
    }

    
    int DraculaSpace = context.board.GetHeroLocation(context.hero->GetId());
    
    auto SameZoneSpaces = context.map.GetSpeacesWithSameZones(DraculaSpace);

    vector<int> AvailableSpaces;

    int counter = 1;
    bool PrintGetSpace = true;

    for(int space : SameZoneSpaces)
    {
        if(!context.board.IsOccupied(space))
        {
            if(PrintGetSpace)
            {
                cout<<"Available spaces\n";
                PrintGetSpace = false;
            }
            cout<<counter<<") Space "<<space<<"\t";
            counter++;
            AvailableSpaces.push_back(space);
        }
    }
    
    cout<<"\nEnter your choice: ";

    int choice;
    cin>>choice;
    while (true)
    {
        if(choice < 1 || choice > AvailableSpaces.size())
        {
            cout<<"Invalid choice.\nEnter again: ";
            cin>>choice;
        }
        else
            break;

    }
    
    DeadSisters[schoice - 1]->Heal(1);

    //cout<<"\ndead sister id: "<<DeadSisters[schoice - 1]->GetId()<<endl;

    context.board.SetHeroLocation(DeadSisters[schoice - 1]->GetId(), AvailableSpaces[choice - 1]);
    cout<<"[Baptism Of Blood] Dead sister now alive and placed in "<<AvailableSpaces[choice - 1]<<".\n";


}

Beastform::Beastform(): Card("Beastform", CardType::Attack, 6, 4, Timing::DuringCombat,
        "DURING COMBAT: You may discard any number of cards from your hand. This card's value is +1 for each card you discard.", CardOwner::Dracula)
{}


void Beastform::ApplyDuringCombat(CombatContext &context)
{
    auto &hand = context.AttackerPlayer->GetHand();

    if(hand.empty())
    {
        cout<<"[Beastform] You have no cards to discard!\n";
        return;
    }

    cout<<"[Beastform] Choose cards to discard.\n";

    int counter = 0;
    while(counter < hand.size())
    {
        cout<<counter + 1<<") "<<hand[counter]->GetName()<<" (Boost: "<<hand[counter]->GetBoost()<<")\t";
        counter++;
    }

    vector<int> choices;
    int x;
    counter++;

    cout<<counter<<") "<<"exit\n";

    cout<<"Enter card number: ";
    cin>>x;

    while(choices.size() <= hand.size())
    {
        if(x == counter)
            break;
        
        if(x >= 1 && x <= hand.size())
        {
            if(find(choices.begin(), choices.end(), x) != choices.end())
            {
                cout<<"You entered this card before.\n";
            }
            else
            {
                choices.push_back(x);
                sort(choices.begin(), choices.end());
                //choices.erase(unique(choices.begin(), choices.end()), choices.end());

            }
            cout<<"You enter card number "<< x <<endl<<"Enter new choice: ";
        }
        else
        {
            cout<<"Invalid choice.\n";
        }
        cin>>x;
    }

    vector<Card*> ToDiscard;

    for(int c : choices)
    {
        if(c >= 1 && c <= hand.size())
        {
            ToDiscard.push_back(hand[c - 1].get());
        }
    }


    int count = ToDiscard.size();

    for(Card* c : ToDiscard)
    {
        context.AttackerPlayer->DiscardCardFromHand(c);
    }

    context.AttackValue += count;

    cout<<"[Beastform] Discarded "<<count<<" cards. Attack +"<<count<<".\n";
    cout<<"New attack value = "<<context.AttackValue<<"\n";

}


Dash::Dash(): Card("Dash", CardType::Versatile, 3, 1, Timing::AfterCombat,
        "AFTER COMBAT: Move your fighter up to 3 spaces.", CardOwner::Any)
{}


void Dash::ApplyAfterCombat(CombatContext &context)
{
    Hero* hero = nullptr;

    if(context.DefenseCard == this)
        hero = context.Defender;
    else
        hero = context.Attacker;

    vector<int> dashmovement = context.movement.GetAvailableMove(3, hero->GetId());

    int counter = 1;
    int current = context.board.GetHeroLocation(hero->GetId());
    
    if(hero->IsDead())
    {
        cout<<"[Dash] Your hero is dead.\n";
        return;
    }

    cout<<"[Dash] Move your fighter up to 3 spaces.\n";
    for(auto& move : dashmovement)
    {
        cout<<counter<<") space "<<move<<"\t";
        counter++;
    }

    int choice;
    cout<<"\nEnter your choice: ";
    while (true)
    {
        cin>>choice;
        if(choice < 1 || choice > dashmovement.size())
        {
            cout<<"Invalid choice. Enter again: ";
        }
        else
            break;
    }

    context.board.SetHeroLocation(hero->GetId(), dashmovement[choice - 1]);

    cout<<"[Dash] "<<hero->GetName()<<" moved from "<<current<<" to "<<dashmovement[choice - 1]<<".\n";
    
}

Exploit::Exploit(): Card("Exploit", CardType::Versatile, 4, 1, Timing::AfterCombat,
        "AFTER COMBAT: Draw 1 card.", CardOwner::Any)
{}

void Exploit::ApplyAfterCombat(CombatContext& context)
{
    Deck* deck = context.AttackerPlayer->GetDeck();

    if(deck->IsEmpty(context.AttackerPlayer->GetHero()->GetTeam()))
    {
        context.AttackerPlayer->GetHero()->TakeDamage(2);
        
        //vector<unique_ptr<Hero>> sidekick;
        auto& sidekick = context.AttackerPlayer->GetSideKicks();

        for(auto& hero: sidekick)
        {
            hero->TakeDamage(2);
        }

        cout<<"[Exploit] Deck empty. drew not success.\n";

        return;
    }

    unique_ptr<Card> drawn = deck->DrawCard(context.AttackerPlayer->GetHero()->GetTeam());

    context.AttackerPlayer->AddCardToHand(move(drawn));

    cout<<"[Exploit] "<<context.AttackerPlayer->GetName()<<" drew 1 card after combat.\n";
}



LookIntoMyEyes::LookIntoMyEyes() : Card("Look Into My Eyes", CardType::Defence, 1, 2, Timing::DuringCombat,
        "DURING COMBAT: Add the BOOST value from your opponent's attack card to the defense value of this card.", CardOwner::Dracula)
{}

void LookIntoMyEyes::ApplyDuringCombat(CombatContext& context)
{
    Card* attackercard = context.AttackCard;

    if(!attackercard)
    {
        cout<<"[Look Into My Eyes] No opponent attack card.\n";
        return;
    }

    context.DefenseValue = attackercard->GetBoost() + context.DefenseCard->GetValue();

    cout<<"[Look Into My Eyes] Added opponent Boost ("<<attackercard->GetBoost()<<") to defense.\n[Look Into My Eyes] New defense = "<<context.DefenseValue<<endl;

}

PreyUpon::PreyUpon() : Card("Prey Upon", CardType::Scheme, 0, 4, Timing::Event,
        "Deal 1 damage to all opposing fighters adjacent to Dracula. Dracula recovers 1 health for each damage dealt.", CardOwner::Dracula)
{}


void PreyUpon::ApplyScheme(SchemeContext& context)
{
    int DraculaSpace = context.board.GetHeroLocation(context.hero->GetId());

    auto AdjacentDracula = context.map.GetAdjacents(DraculaSpace);
    
    int counter = 0;
    for(auto adj : AdjacentDracula)
    {
        if(context.board.IsOccupiedByEnemy(adj, context.hero->GetId()))
        {
            context.board.GetHeroBySpace(adj)->TakeDamage(1);
            context.hero->Heal(1);
            counter++;
        }
    }

    if(counter == 0)
    {
        cout<<"[Prey Upon] No adjacent enemies.\n";
        return;
    }
    else
    {
        cout<<"[Prey Upon] Take "<<counter<<" damage to enemies and Dracula heal "<<counter<<".\n";
    }
}



RaveningSeduction::RaveningSeduction() : Card("Ravening Seduction", CardType::Scheme, 0, 2, Timing::Event,
        "Move any fighter up to 2 spaces. After moving, deal 1 damage to the moved fighter for each Sister adjacent to them.", CardOwner::Sisters)
{}

void RaveningSeduction::ApplyScheme(SchemeContext& context)
{
    vector<Hero*> AllHeroes;

    for(auto& h : context.player->GetAliveHeroes())
        AllHeroes.push_back(h);

    for(auto& h : context.OpponentPlayer->GetAliveHeroes())
        AllHeroes.push_back(h);

    context.terminalview.display();

    cout<<"Available hero:\n";
    for(int i = 0; i < AllHeroes.size(); i++ )
    {
        cout<<i+1<<") "<<AllHeroes[i]->GetName()<<"\t";
    }

    cout<<"\nChoose a hero to move: ";
    int choice;
    cin>>choice;

    while(choice < 1 || choice > AllHeroes.size())
    {
        cout<<"Invalid choice. Enter again: ";
        cin>>choice;
    }


    Hero* target = AllHeroes[choice - 1];
    //int TargetLocation = context.board.GetHeroLocation(target->GetId());
    
  //  cout << "Target ID = " << target->GetId() << endl;
   // cout << "TargetLocation = " << TargetLocation << endl;

    
    auto moves = context.movement.GetAvailableMove(2, target->GetId());

    if(moves.empty())
    {
        cout<<"No available spaces.\n";
        return;
    }

    cout<<"Available space\n";

    for(int i = 0; i < moves.size(); i++)
        cout<<i+1<<") Space "<<moves[i]<<"\t";
    
    cout<<"\nChoose destination: ";

    int destchoice;
    cin>>destchoice;
    
    while(destchoice < 1 || destchoice > moves.size())
    {
        cout<<"Invalid destination. Enter again: ";
        cin>>destchoice;
    }

    int dest = moves[destchoice - 1];

    context.board.SetHeroLocation(target->GetId(), dest);

    auto adj = context.map.GetAdjacents(dest);
    int damage = 0;
    for(auto space : adj)
    {
        if(context.board.IsOccupied(space))
        {
            Hero* h = context.board.GetHeroBySpace(space);
            if(h->GetName() == "Sister")
                damage++;
        }
    }

    target->TakeDamage(damage);
    cout<<"[Ravening Seduction] " << target->GetName()<< " Moved and get " << damage << " damage from adjacent sisters.\n";




    cout << "AFTER CARD SET:" << endl;

    cout << "Hero pos: "
    << context.board.GetHeroLocation(target->GetId())
    << endl;

    cout << "Occupied: "
    << context.board.GetOccupiedHeroId(dest)
    << endl;

}

ThirstForSustenance::ThirstForSustenance(): Card("Thirst for Sustenance", CardType::Attack, 3, 3, Timing::AfterCombat,
        "AFTER COMBAT: If you won the combat, place Dracula in any space adjacent to the opposing fighter.", CardOwner::Sisters)
{}

void ThirstForSustenance::ApplyAfterCombat(CombatContext& context)
{
    if(!context.AttackerWin)
    {
        cout<<"[Thirst For Sustenance] Combat lost. No effect!\n";
        return;
    }
    
    vector<int> AdjacentDefender = context.map.GetAdjacents(context.board.GetHeroLocation(context.Defender->GetId()));

    vector<int> AvailableAdjacent;
    
    for(auto adj : AdjacentDefender)
    {
        if(!context.board.IsOccupied(adj))
            AvailableAdjacent.push_back(adj);   
    }

    if(AvailableAdjacent.empty())
    {
        cout<<"[Thirst For Sustenance] No Adjacent spaces available!\n";
        return;
    }

    cout<<"[Thirst For Sustenance] adjacent space\n";
    int counter = 1;
    for(int space : AvailableAdjacent)
    {
        cout<<counter<<") "<<space<<"\t";
        counter++;
    }
    
    cout<<"\nEnter your choice: ";
    int choice;
    while (true)
    {
        cin>>choice;
        if(choice < 0 || choice > AvailableAdjacent.size())
        {
            cout<<"Invalid choice. Try again: ";
        }
        else
            break;
    }

    context.board.SetHeroLocation(context.AttackerPlayer->GetHero()->GetId() ,AvailableAdjacent[choice - 1]);
    cout<<"[Thirst For Sustenance] Dracula moved to space "<<AvailableAdjacent[choice - 1]<<".\n";

}

Feint::Feint(): Card("Feint", CardType::Versatile, 2, 2, Timing::Immediately,
        "IMMEDIATELY: Cancel all effects on your opponent's card.", CardOwner::Any)
{}

void Feint::ApplyImmediately(CombatContext& context)
{
    context.CancelOpponentEffects = true;

    cout<<"[Feint] Cancel opponent's card effects.\n";
}

// =================================== Sherlock holmes ===================================


AdministerAid::AdministerAid() : Card("Administer Aid", CardType::Scheme, 0, 2, Timing::Event, 
    "Place Dr. Watson in a space adjacent to Holmes. Holmes recovers 1 health. Draw 1 card.",CardOwner::DrWatson)
{}

void AdministerAid::ApplyScheme(SchemeContext& context)
{
    context.terminalview.display();

    auto& sidekicks = context.player->GetSideKicks();

    Hero* Watson = nullptr;

    for(auto& side : sidekicks)
    {
        if(side->GetName() == "Watson")
        {
            Watson = side.get();
            break;        
        }
    }

    if(!Watson)
    {
        cout<<"[Administer Aid] Watson is not available.\n";
        return;
    }

    int SherlockSpace = context.board.GetHeroLocation(context.hero->GetId());
    auto adj = context.map.GetAdjacents(SherlockSpace);

    vector<int> AvailableSpaces;

    for(int space : adj)
    {
        if(!context.board.IsOccupied(space))
            AvailableSpaces.push_back(space);
    }

    if(AvailableSpaces.empty())
    {
        cout<<"[Administer Aid] No adjacent free spaces.\n";
        return;
    }
    
    cout<<"[Administer Aid] Choose a space to place Watson:\n";
    for(int i = 0; i < AvailableSpaces.size(); i++)
        cout<<i + 1<<") "<<AvailableSpaces[i]<<"\t";

    int choice;
    cin>>choice;

    while(choice < 1 || choice > AvailableSpaces.size())
    {
        cout<<"Invalid choice. Enter again: ";
        cin>> choice;
    }

    int TargetSpace = AvailableSpaces[choice - 1];
    context.board.SetHeroLocation(Watson->GetId() ,TargetSpace);

    context.hero->Heal(1);
    unique_ptr<Card> card = context.player->GetDeck()->DrawCard(context.player->GetHero()->GetTeam());
    context.player->AddCardToHand(move(card));

    cout<<"[Administer Aid] Watson placed next to Holmes. Holmes healed 1 HP and drew 1 card.\n";
}



// class ConfirmSuspicion : public Card


Counterpunch::Counterpunch() : Card("Counterpunch", CardType::Versatile, 3, 1, Timing::AfterCombat,
    "AFTER COMBAT: If Holmes is adjacent to the opposing fighter, deal 2 damage to that fighter.", CardOwner::SherlockHolmes)
{}


void Counterpunch::ApplyAfterCombat(CombatContext& context)
{
    int AttackerSpace = context.board.GetHeroLocation(context.Attacker->GetId());
    int DefenderSpace = context.board.GetHeroLocation(context.Defender->GetId());

    auto adj = context.map.GetAdjacents(AttackerSpace);

    bool adjacent = false;

    for(int space : adj)
    {
        if(space == DefenderSpace)
        {
            adjacent = true;
            break;
        }
    }

    if(adjacent)
    {
        context.Defender->TakeDamage(2);
        cout<<"[Counterpunch] "<<context.Attacker->GetName()<<" hit 2 damage to "<<context.Defender->GetName()<<" after combat.\n";
    }
    else
    {
        cout<<"[Counterpunch] Enemy is not adjacent. No damage.\n";
    }

}
