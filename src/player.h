#pragma once

#include "projectile.h"
#include "entity.h"
#include <memory>
#include <vector>
#include "textureLoader.h"

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
	int score;

	Texture2D texture;

	Player(float x, float y, int penetration, float attackSpeed, Texture2D texture);
	void shoot(const int mousePosX, const int mousePosY, std::vector<std::unique_ptr<Projectile>>& projectileVector, TextureLoader& textureLoader);
	Player();

	void draw();
};
