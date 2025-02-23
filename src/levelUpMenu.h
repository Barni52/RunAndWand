#pragma once

#include "raylib.h"
#include "button.h"
#include "collision.h"
#include "player.h"

class LevelUpMenu {
public:
	LevelUpMenu();
	bool draw(int screenWidth, int screenHeight, Player& player) const;
};