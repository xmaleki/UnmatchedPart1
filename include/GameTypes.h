#pragma once
/*
#include "Player.h"
#include "Board.h"
#include "Map.h"
#include "Movement.h"
#include "TerminalView.h"
*/
class Board;
class Map;
class Player;
class Movement;
class Card;
class Hero;
class TerminalView;

enum class ZoneTypes{
    LightBlue,
    DarkBlue,
    Gray,
    Green,
    Purple,
    Yellow,
    Brown
};

enum class HeroesTeam
{
    DRACULA,
    SHERLOCK,
    WITHOUTTEAM
};

enum class AttackType
{
    MELEE,
    RANGED
};

enum class CardType
{
    Attack, // red
    Defence, // blue
    Versatile, // purple
    Scheme // yellow
};

enum class Timing
{
    Immediately,
    DuringCombat,
    AfterCombat,
    Event
};

enum class CardOwner
{
    SherlockHolmes,
    DrWatson,
    Dracula,
    Sisters,
    Any
};