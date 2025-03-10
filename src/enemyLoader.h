#pragma once

#include "enemy.h"
#include <vector>
#include <memory>
#include "player.h"
#include <cmath>
#include <cstdlib>
#include "textureLoader.h"
#include "textureLoader.h"

class EnemyLoader {
public:
	int currentLevel;
	int maxEnemies;
	int numberOfEnemiesLeftToSpawn;
	float lastTimeEnemySpawned;
	float enemySpawnRate;
	float enemySpeedRate;
	float enemyHealth;
	double experienceFromEnemies;
	TextureLoader textureLoader;

	EnemyLoader();
	void loadEnemies(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player);

	void setTextureLoader(const TextureLoader& textureLoader) {
		this->textureLoader = textureLoader;
	}

private:
	void spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player);
	void spawnNextLevel();
};