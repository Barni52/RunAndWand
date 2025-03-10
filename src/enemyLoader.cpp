#define _USE_MATH_DEFINES
#include "enemyLoader.h"
#include <iostream>

EnemyLoader::EnemyLoader() : currentLevel(1), maxEnemies(6), numberOfEnemiesLeftToSpawn(6), lastTimeEnemySpawned((float)GetTime()), enemySpawnRate(1.0f),
enemySpeedRate(180), experienceFromEnemies(5), enemyHealth(1.0f) {}

void EnemyLoader::loadEnemies(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player) {
	if ((float)GetTime() - lastTimeEnemySpawned >= enemySpawnRate && numberOfEnemiesLeftToSpawn > 0) {
		lastTimeEnemySpawned = (float)GetTime();
		spawnEnemy(enemyVector, player);
		numberOfEnemiesLeftToSpawn--;
	}
	if (numberOfEnemiesLeftToSpawn <= 0){
		spawnNextLevel();
	}
}

void EnemyLoader::spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player) {
	const float spawnRadius = 1500.0f;
	float angle = (float)(rand()) / RAND_MAX * 2 * M_PI; // Random angle (0 to 2pi)

	float spawnX = player.x + spawnRadius * cos(angle);
	float spawnY = player.y + spawnRadius * sin(angle);

	enemyVector.push_back(std::make_unique<Enemy>(spawnX, spawnY, enemySpeedRate, enemyHealth, experienceFromEnemies, textureLoader.enemyTexture1));
}

void EnemyLoader::spawnNextLevel() {
	currentLevel++;
	enemySpawnRate *= 0.9f;
	enemySpeedRate *= 1.03f;
	experienceFromEnemies *= 1.1;
	enemyHealth *= 1.05f;
	if (maxEnemies < 10) {
		maxEnemies += 2;
	}
	else {
		maxEnemies = (int)(1.10 * maxEnemies);
	}
	numberOfEnemiesLeftToSpawn = maxEnemies;
}