#include "enemy.h"
#include "raylib.h"
#include "map.h"
#include <iostream>


Enemy::Enemy(float x, float y, int health) : Entity(x, y, 20), speed(300), keepAlive(true), health(health) {};

void Enemy::draw() const {
	DrawRectangle( (int)x, (int)y , (int)width, (int)width, RED);
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