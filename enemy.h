#pragma once

#include <vector>
#include "player.h"

class Enemy {
public:
	float enemyX;
	float enemyY;
	float speed;

	bool keepAlive;

	Enemy(float enemyX, float enemyY);
	void draw() const;
	void update(float deltaTime, Player& player);
};

void drawEnemies(const std::vector<std::unique_ptr<Enemy>>& enemyVector);
void updateEnemies(std::vector<std::unique_ptr<Enemy>>& enemyVector, const float deltaTime, Player& player);