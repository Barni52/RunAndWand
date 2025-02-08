#pragma once

#include "raylib.h"
#include <vector>
#include "map.h"

class Player;

class Projectile {
public:
	Projectile(Player player, float directionX, float directionY);

	float positionX;
	float positionY;

	float directionX;
	float directionY;

	bool friendly;
	float speed;

	bool keepAlive;
	int aliveTime;

	void draw();
	void update(float deltaTime);
};

void drawProjectiles(std::vector<Projectile> projectileVector);
void updateProjectiles(std::vector<Projectile>& projectileVector, float deltaTime);
