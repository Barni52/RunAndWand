#include "enemy.h"
#include "raylib.h"
#include "map.h"


Enemy::Enemy(float enemyX, float enemyY) : enemyX(enemyX), enemyY(enemyY), speed(300){};

void Enemy::draw() const {
	DrawRectangle(((int)enemyX + 1 * TILE_SIZE), ((int)enemyY + 1 * TILE_SIZE), 2 * TILE_SIZE, 2 * TILE_SIZE, RED);
}

void Enemy::update(float deltaTime, Player& player) {
	float directionX = enemyX - player.playerX;
	float directionY = enemyY - player.playerY;

	float length = sqrt(directionX * directionX + directionY * directionY);
	if (length != 0) { // Prevent division by zero
		directionX /= length;
		directionY /= length;
	}

	this->enemyX -= directionX * speed * deltaTime;
	this->enemyY -= directionY * speed * deltaTime;
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