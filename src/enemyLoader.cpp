#define _USE_MATH_DEFINES
#include "enemyLoader.h"

EnemyLoader::EnemyLoader() : currentLevel(1), numberOfEnemiesLeft(10), lastTimeEnemySpawned((float)GetTime()) {

}

bool EnemyLoader::loadEnemies(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player) {
	if ((float)GetTime() - lastTimeEnemySpawned >= 1 && numberOfEnemiesLeft > 0) {
		lastTimeEnemySpawned = (float)GetTime();
		spawnEnemy(enemyVector, player);
		numberOfEnemiesLeft--;
	}
	if (numberOfEnemiesLeft <= 0 && enemyVector.empty()){
		numberOfEnemiesLeft = 10;
		return true;
	}
	return false;
}

void EnemyLoader::spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player) {
	const float spawnRadius = 1200.0f;
	float angle = (float)(rand()) / RAND_MAX * 2 * M_PI; // Random angle (0 to 2pi)

	float spawnX = player.x + spawnRadius * cos(angle);
	float spawnY = player.y + spawnRadius * sin(angle);

	enemyVector.push_back(std::make_unique<Enemy>(spawnX, spawnY, 1));
}