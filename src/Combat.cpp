#include "Combat.h"
#include "Movement.h"
#include <iostream>

Combat::Combat(Board& b, Map& m, Movement&mv):board(b), map(m), movement(mv)
{}

void Combat::StartCombat(Player* AttackerPlayer, Player* DefenderPlayer,
                        Hero* Attacker, Hero* Defender, Card* AttackCard)
{
    CombatContext combatcontext
    {
        AttackerPlayer, DefenderPlayer, Attacker, Defender, AttackCard->GetValue(), 0, board, map, movement, AttackCard
    };

    cout<<"==========================================\n";
    cout<<"Combat\n";
    cout<<"==========================================\n";

    cout<<"-------------------- Before Combat --------------------\n";
    cout<<"Attacker HP: "<<Attacker->GetHP()<<endl;
    cout<<"Defender HP: "<<Defender->GetHP()<<endl;
    cout<<"-------------------- Before Combat --------------------\n";
    
    // system combat bayad ghabl az ejraye code ha, feint ro baraye cancel kardan check kone.

    cout<<Attacker->GetName()<<" attacks "<<Defender->GetName()<<" !\n";
    
    AttackerPlayer->DiscardCardFromHand(AttackCard);

    Card* DefenderCard = nullptr;

    auto& DeffenderHand = DefenderPlayer->GetHand();
    vector<int> PlayableDefenderCards;
    
    int counter = 1;

    for(int i = 0; i < DeffenderHand.size(); i++)
    {
        Card* c = DeffenderHand[i].get();
        if(c->GetType() == CardType::Defence || c->GetType() == CardType::Versatile)
        {
            PlayableDefenderCards.push_back(i);
            cout<<counter<<") "<<c->GetName()<<" (Value:"<<c->GetValue()<<") "<<"["<<c->ToStringType(c->GetType())<<"]"<<"\n";
            counter++;
        }
    }
    

    if(!PlayableDefenderCards.empty())
    {
        cout<<counter<<") Play no defense card\n";

        while (true)
        {
            cout<<"Please enter the card for defense: ";
            int choice;
            cin>>choice;

            if(choice == counter)
            {
                //cout<<"No choice\n";
                break;
            }
            else if(choice > 0 && choice <= PlayableDefenderCards.size())
            {
                DefenderCard = DeffenderHand[PlayableDefenderCards[choice - 1]].get();
                DefenderPlayer->DiscardCardFromHand(DefenderCard);
                combatcontext.DefenseCard = DefenderCard;
                break;
            }
            else
            {
                cout<<"Invalid choice. try again!\n";
            }
        }
    }
    else
    {
        cout<<"Defender has no defense cards.\n";
        DefenderCard = nullptr;
    }
    

    cout<<"Attacker played : "<<AttackCard->GetName()<<"\n";
    if(DefenderCard)
    {
        cout<<"Defender played: "<<DefenderCard->GetName()<<"\n";
    }
    else
    {
        cout<<"Defender played no card.\n";
    }

    bool DefenderPlayedFeint = (DefenderCard && DefenderCard->GetName() == "Feint");
    bool AttackerPlayedFeint = (AttackCard->GetName() == "Feint");

    bool SherlockDSAP = (DefenderCard) && (DefenderCard->GetOwner() == CardOwner::SherlockHolmes || DefenderCard->GetOwner() == CardOwner::DrWatson); 
    bool SherlockASAP = (AttackCard->GetOwner() == CardOwner::SherlockHolmes || AttackCard->GetOwner() == CardOwner::DrWatson);

    // immediately
    if(DefenderCard)
        DefenderCard->ApplyImmediately(combatcontext);
    
    if(!DefenderPlayedFeint || SherlockASAP)
        AttackCard->ApplyImmediately(combatcontext);

    // during combat
    if(DefenderCard)
    {
        if(!AttackerPlayedFeint || SherlockDSAP)
            DefenderCard->ApplyDuringCombat(combatcontext);
    }

    if(!DefenderPlayedFeint || SherlockASAP)
        AttackCard->ApplyDuringCombat(combatcontext);

    if(combatcontext.DefenseValue == 0 && DefenderCard)
    {
        combatcontext.DefenseValue = DefenderCard->GetValue();
    }

    int Damage = combatcontext.AttackValue - combatcontext.DefenseValue;
    
    if(Damage < 0)
    {
        Damage = 0;
        combatcontext.AttackerWin = false;
    }
    cout<<"Damage = "<<Damage<<"\n";

    if(Damage > 0)
    {
        Defender->TakeDamage(Damage);
        cout<<Defender->GetName()<<" takes "<<Damage<<" damage!\n";
        combatcontext.AttackerWin = true;
    }
    else
    {
        cout<<"No Damage dealt.\n";
    }

    // after combat effect
    if(DefenderCard)
    {
        if(!AttackerPlayedFeint || SherlockDSAP)
            DefenderCard->ApplyAfterCombat(combatcontext);
    }

    if(!DefenderPlayedFeint || SherlockASAP)
        AttackCard->ApplyAfterCombat(combatcontext);

    cout<<"-------------------- After Combat --------------------\n";
    cout<<"Attacker HP: "<<Attacker->GetHP()<<endl;
    cout<<"Defender HP: "<<Defender->GetHP()<<endl;
    cout<<"-------------------- After Combat --------------------\n";

    cout<<"==========================================\n";
    cout<<"Combat Ended\n";
    cout<<"==========================================\n";

}

vector<Hero*> Combat::GetValidTargets(Hero* attacker)
{
    vector<Hero*> result;

    int AttackerSpace = board.GetHeroLocation(attacker->GetId());

    if(attacker->GetAttackType() == AttackType::MELEE)
    {
        for(int neighbor : map.GetAdjacents(AttackerSpace))
        {
            if(board.IsOccupiedByEnemy(neighbor, attacker->GetId()))
            {
                Hero* enemy = board.GetHeroBySpace(neighbor);
                if(enemy && !enemy->IsDead())
                    result.push_back(enemy);
            }
        }
    }
    else // RANGED
    {
        const auto& AttackerZones = map.GetSpace(AttackerSpace).GetZones();

        for(int space = 0; space < 32; space++)
        {
            if(board.IsOccupiedByEnemy(space, attacker->GetId()))
            {
                Hero* enemy = board.GetHeroBySpace(space);
                if(!enemy || enemy->IsDead())
                    continue;

                const auto& enemyZones = map.GetSpace(space).GetZones();
                bool SameZone = false;

                for(auto hz : AttackerZones)
                {
                    for(auto ez : enemyZones)
                    if(hz == ez)
                        SameZone = true;
                }

                if(SameZone)
                    result.push_back(enemy);
            }
        }
    }
    return result;
}


