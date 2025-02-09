#include "player.h"

Player::Player(float playerX, float playerY) : playerX(playerX), playerY(playerY), speed(10) {}

Projectile Player::shoot(Player player, int mousePosX, int mousePosY) {
	Projectile projectile(player, (float)mousePosX, (float)mousePosY);
	return projectile;
}