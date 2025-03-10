#pragma once

#include <vector>
#include "player.h"
#include "entity.h"
#include "textureLoader.h"

class Enemy : public Entity{
public:
	
	float speed;

	bool keepAlive;

	float maxHealth;
	float currentHealth;

	double experience;

	Texture2D texture;

	Enemy(float x, float y, float speed, float maxHealth, double experience, Texture2D texture);
	void draw() const;
	void update(float deltaTime, Player& player);

};

void drawEnemies(const std::vector<std::unique_ptr<Enemy>>& enemyVector);
void updateEnemies(std::vector<std::unique_ptr<Enemy>>& enemyVector, const float deltaTime, Player& player);