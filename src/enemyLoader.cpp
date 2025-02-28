#define _USE_MATH_DEFINES
#include "enemyLoader.h"

EnemyLoader::EnemyLoader() : currentLevel(1), maxEnemies(6), numberOfEnemiesLeft(6), lastTimeEnemySpawned((float)GetTime()), enemySpawnRate(1.0f), enemySpeedRate(300) {}

bool EnemyLoader::loadEnemies(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player) {
	if ((float)GetTime() - lastTimeEnemySpawned >= 1 && numberOfEnemiesLeft > 0) {
		lastTimeEnemySpawned = (float)GetTime();
		spawnEnemy(enemyVector, player);
		numberOfEnemiesLeft--;
	}
	if (numberOfEnemiesLeft <= 0 && enemyVector.empty()){
		levelUp();

		//Indicates that the player has killed all enemies, and the level up menu is shown
		return true;
	}
	return false;
}

void EnemyLoader::spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player) {
	const float spawnRadius = 1200.0f;
	float angle = (float)(rand()) / RAND_MAX * 2 * M_PI; // Random angle (0 to 2pi)

	float spawnX = player.x + spawnRadius * cos(angle);
	float spawnY = player.y + spawnRadius * sin(angle);

	enemyVector.push_back(std::make_unique<Enemy>(spawnX, spawnY, enemySpeedRate, 2));
}

void EnemyLoader::levelUp() {
	currentLevel++;
	enemySpawnRate *= 0.80f;
	enemySpeedRate *= 1.05f;
	if (maxEnemies < 10) {
		maxEnemies += 2;
	}
	else {
		maxEnemies = (int)(1.10 * maxEnemies);
	}
	numberOfEnemiesLeft = maxEnemies;
}