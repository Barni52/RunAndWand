#include "enemy.h"
#include "raylib.h"
#include "map.h"
#include <iostream>


Enemy::Enemy(float x, float y, float speed, int maxHealth, double experience) : Entity(x, y, 20), keepAlive(true), speed(speed), 
maxHealth(maxHealth), currentHealth(maxHealth), experience(experience) {};

void Enemy::draw() const {
	// Draw enemy
	DrawRectangle((int)x, (int)y, (int)width, (int)width, RED);

	// Health bar properties
	float healthBarWidth = width;
	float healthBarHeight = 5;
	float healthBarX = x;
	float healthBarY = y - 10;

	// Background bar
	DrawRectangle((int)healthBarX, (int)healthBarY, (int)healthBarWidth, (int)healthBarHeight, DARKGRAY);

	// Foreground health bar
	float healthPercentage = (float)currentHealth / (float)maxHealth;
	DrawRectangle((int)healthBarX, (int)healthBarY, (int)(healthBarWidth * healthPercentage), (int)healthBarHeight, GREEN);
}


void Enemy::update(float deltaTime, Player& player) {
	float directionX = x - player.x;
	float directionY = y - player.y;

	float length = (float)sqrt(directionX * directionX + directionY * directionY);

	float stopThreshold = 3.0f;
	if (length <= stopThreshold) {
		return; // Stop movement
	}

	if (length != 0) { // Prevents division by zero
		directionX /= length;
		directionY /= length;
	}

	x -= directionX * speed * deltaTime;
	y -= directionY * speed * deltaTime;
}

void drawEnemies(const std::vector<std::unique_ptr<Enemy>>& projectileVector) {
	for (int i = 0; i < projectileVector.size(); i++) {
		projectileVector[i]->draw();
	}


}

void updateEnemies(std::vector<std::unique_ptr<Enemy>>& enemyVector, const float deltaTime, Player& player) {
	for (int i = 0; i < enemyVector.size(); i++) {
		enemyVector[i]->update(deltaTime, player);
		if (enemyVector[i]->keepAlive == false) {
			enemyVector.erase(enemyVector.begin() + i);
			i--;
		}
	}
}