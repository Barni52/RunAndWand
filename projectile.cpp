#include "projectile.h"
#include "player.h"
#include "raylib.h"
#include "map.h"
#include <iostream>

Projectile::Projectile(Player player, float directionX, float directionY) : positionX(player.playerX), positionY(player.playerY)
,speed(50) , friendly(true), keepAlive(true), aliveTime(0) {
	this->directionX = player.playerX - directionX;
	this->directionY = player.playerY - directionY;

	float length = sqrt(this->directionX * this->directionX + this->directionY * this->directionY);
	if (length != 0) { // Prevent division by zero
		this->directionX /= length;
		this->directionY /= length;
	}
};

void Projectile::draw() {
	DrawRectangle((positionX + 1) * TILE_SIZE, (positionY + 1) * TILE_SIZE, 1 * TILE_SIZE, 1 * TILE_SIZE, YELLOW);
}
void Projectile::update(float deltaTime) {
	this->positionX -= directionX * speed * deltaTime;
	this->positionY -= directionY * speed * deltaTime;
	aliveTime++;

	if (aliveTime > 180) {
		this->keepAlive = false;
	}
	
}


void drawProjectiles(std::vector<Projectile> projectileVector) {
	for (int i = 0; i < projectileVector.size(); i++) {
		projectileVector[i].draw();
	}
}

void updateProjectiles(std::vector<Projectile>& projectileVector, float deltaTime) {
	for (int i = 0; i < projectileVector.size(); i++) {
		projectileVector[i].update(deltaTime);
		if (projectileVector[i].keepAlive == false) {
			projectileVector.erase(projectileVector.begin() + i);
			i--;
		}
	}
}



