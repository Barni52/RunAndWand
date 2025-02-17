#pragma once

#include "raylib.h"
#include "button.h"

class Menu {
public:
	Menu();
	bool draw(int screenWidth, int screenHeight) const;
};