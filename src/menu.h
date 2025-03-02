#pragma once

#include "raylib.h"
#include "button.h"
#include "collision.h"
#include <string>

class Menu {
public:
	Menu();
	bool draw(int highscore) const;
};