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
