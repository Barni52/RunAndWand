#pragma once

#include "raylib.h"
#include <vector>
#include "map.h"
#include "entity.h"
#include <memory>
#include <unordered_set>

class Player;

class Projectile : public Entity{
public:
	Projectile(Player player, float directionX, float directionY, int penetration);

	float directionX;
	float directionY;

	bool friendly;
	float speed;

	int penetration;

	bool keepAlive;
	int aliveTime;

	std::unordered_set<int> shotEnemyIdSet;

	void draw() const;
	void update(float deltaTime);
};

void drawProjectiles(const std::vector<std::unique_ptr<Projectile>>& projectileVector);
void updateProjectiles(std::vector<std::unique_ptr<Projectile>>& projectileVector, float deltaTime);
