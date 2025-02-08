#include "player.h"

Player::Player(int playerX, int playerY) : playerX(playerX), playerY(playerY) {}

Projectile Player::shoot(Player player, int mousePosX, int mousePosY) {
	Projectile projectile(player, (float)mousePosX, (float)mousePosY);
	return projectile;
}