#pragma once

#include "raylib.h"
#include "button.h"
#include "collision.h"

class LevelUpMenu {
public:
	LevelUpMenu();
	bool draw(int screenWidth, int screenHeight) const;
};