#pragma once

#include "projectile.h"
#include "entity.h"

class Player : public Entity{
public:
	int maxHealth;
	int health;
	float speed;

	Player(float x, float y);
	Projectile shoot(const int mousePosX, const int mousePosY);

	void draw();
};
