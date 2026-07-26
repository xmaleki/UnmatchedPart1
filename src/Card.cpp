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
