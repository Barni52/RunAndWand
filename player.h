#pragma once

#include "projectile.h"

class Player {
public:
	int playerX;
	int playerY;
	Player(int playerX, int playerY);
	Projectile shoot(Player player, int mousePosX, int mousePosY);
};
