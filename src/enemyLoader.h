#pragma once

#include "enemy.h"
#include <vector>
#include <memory>
#include "player.h"
#include <cmath>
#include <cstdlib>

class EnemyLoader {
public:
	int currentLevel;
	int maxEnemies;
	int numberOfEnemiesLeft;
	float lastTimeEnemySpawned;
	float enemySpawnRate;
	float enemySpeedRate;

	EnemyLoader();
	bool loadEnemies(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player);

private:
	void spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player);
	void levelUp();
};