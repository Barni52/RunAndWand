#pragma once

#include "raylib.h"
#include "button.h"
#include "collision.h"
#include "player.h"

class LevelUpMenu {
private:
	int halfUpgrades = 0;

public:
	LevelUpMenu();
	bool draw(Player& player) const;
};