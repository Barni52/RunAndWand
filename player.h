#pragma once

#include "projectile.h"

class Player {
public:
	float playerX;
	float playerY;
	float speed;

	Player(float playerX, float playerY);
	Projectile shoot(Player player, int mousePosX, int mousePosY);
};
