#include "player.h"

Player::Player(float playerX, float playerY) : playerX(playerX), playerY(playerY), speed(8) {}

Projectile Player::shoot(const Player& player, const int mousePosX, const int mousePosY) {
	Projectile projectile(player, (float)mousePosX, (float)mousePosY);
	return projectile;
}