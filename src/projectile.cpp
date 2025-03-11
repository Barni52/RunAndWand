#include "projectile.h"
#include "player.h"
#include "raylib.h"
#include "map.h"
#include <iostream>

Projectile::Projectile(Player player, float directionX, float directionY, int penetration, Texture2D texture) : 
	Entity(player.x + 1 * TILE_SIZE, player.y + 1 * TILE_SIZE, 10)
,speed(1000) , friendly(true), keepAlive(true), aliveTime(0), penetration(penetration), texture(texture) {
	this->directionX = player.x - directionX;
	this->directionY = player.y - directionY;

	float length = sqrt(this->directionX * this->directionX + this->directionY * this->directionY);
	if (length != 0) { // Prevent division by zero
		this->directionX /= length;
		this->directionY /= length;
	}
	else {
		keepAlive = false; // this ensures that if the normalized vector is zero (aka the vector doesnt have a direction to go), that it gets deleted
	}

	shotEnemyIdSet = std::unordered_set<int>();
};

void Projectile::draw() const{
	//DrawRectangle(((int)x), ((int)y), (int)width, (int)width, YELLOW);

	//Magic numbers
	float scale = 0.35f;
	float adjustX = 5.0f;
	float adjustY = 4.0f;

	Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
	Rectangle dest = { x, y, texture.width * scale, texture.height * scale };

	// Start with the center of the texture as the origin
	Vector2 origin = { (texture.width * scale) / 2, (texture.height * scale) / 2 };

	origin.x -= adjustX;
	origin.y -= adjustY;

	DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}
void Projectile::update(float deltaTime) {
	this->x -= directionX * speed * deltaTime;
	this->y -= directionY * speed * deltaTime;
	aliveTime++;

	if (aliveTime > 180) {
		this->keepAlive = false;
	}
	
}


void drawProjectiles(const std::vector<std::unique_ptr<Projectile>>& projectileVector){
	for (int i = 0; i < projectileVector.size(); i++) {
		projectileVector[i]->draw();
	}
}

void updateProjectiles(std::vector<std::unique_ptr<Projectile>>& projectileVector, const float deltaTime) {
	for (int i = 0; i < projectileVector.size(); i++) {
		projectileVector[i]->update(deltaTime);
		if (projectileVector[i]->keepAlive == false) {
			projectileVector.erase(projectileVector.begin() + i);
			i--;
		}
	}
}



