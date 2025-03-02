#pragma once

#include "projectile.h"
#include "entity.h"
#include <memory>
#include <vector>

class Player : public Entity{
public:

	float speed;
	int penetration;
	float attackSpeed;
	float lastShot;
	float damage;

	int level;
	double currentExperience;
	double experienceToNextLevel;

	Player(float x, float y, int penetration, float attackSpeed);
	void shoot(const int mousePosX, const int mousePosY, std::vector<std::unique_ptr<Projectile>>& projectileVector);

	void draw();
};
