#pragma once

#include <vector>
#include "player.h"
#include "entity.h"

class Enemy : public Entity{
public:
	 
	float speed;

	bool keepAlive;

	int maxHealth;
	int currentHealth;

	double experience;

	Enemy(float x, float y, float speed, int maxHealth, double experience);
	void draw() const;
	void update(float deltaTime, Player& player);

};

void drawEnemies(const std::vector<std::unique_ptr<Enemy>>& enemyVector);
void updateEnemies(std::vector<std::unique_ptr<Enemy>>& enemyVector, const float deltaTime, Player& player);