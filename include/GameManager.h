#pragma once
#include "Map.h"
#include "Board.h"
#include "Hero.h"
#include "Player.h"
#include "TerminalView.h"
#include "Movement.h"
#include "Combat.h"
#include <vector>

class GameManager
{
    private:
        std::unique_ptr<Map> GameMap;
        std::unique_ptr<Board> board;
        std::unique_ptr<Player> player1;
        std::unique_ptr<Player> player2;
        std::unique_ptr<Movement> movement;
        std::unique_ptr<Combat> combat;
        Player* CurrentPlayer = nullptr;
        Player* OpponentPlayer = nullptr;

    public:
        GameManager();
        void StartGame();
        void InitializeHeroes();
        void InitializeHeroesPositions();
        void InitializeSidekicksPositions(Player *, int);
        bool IsGameOver();
        void ShowHand();
        void PlayerTurn();
        void Maneuver(Player &, TerminalView &);
        void Run();
        bool CanPlayCard(const Card*, Hero*);
        Hero* ChooseAttackerForCombat(Card*);
        Hero* ChooseDefenderForCombat(Hero*);

};