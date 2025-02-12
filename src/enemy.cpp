#include "enemy.h"
#include "raylib.h"
#include "map.h"


Enemy::Enemy(float x, float y) : Entity(x, y, 20), speed(300), keepAlive(true) {};

void Enemy::draw() const {
	DrawRectangle(((int)x + 1 * TILE_SIZE), ((int)y + 1 * TILE_SIZE), width, width, RED);
}

void Enemy::update(float deltaTime, Player& player) {
	float directionX = x - player.x;
	float directionY = y - player.y;

	float length = (float)sqrt(directionX * directionX + directionY * directionY);
	if (length != 0) { // Prevent division by zero
		directionX /= length;
		directionY /= length;
	}

	this->x -= directionX * speed * deltaTime;
	this->y -= directionY * speed * deltaTime;
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