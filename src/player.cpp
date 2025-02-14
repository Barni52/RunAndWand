#include "player.h"

Player::Player(float x, float y) : Entity(x, y, 30), maxHealth(100), health(40), speed(8) {}

Projectile Player::shoot(const int mousePosX, const int mousePosY) {
	Projectile projectile(*this, (float)mousePosX, (float)mousePosY);
	return projectile;
}

void Player::draw() {
	// Draw the player
	DrawRectangle((int)x, (int)y, (int)width, (int)width, BLUE);

	//Draw the health bar
	DrawRectangle((int)x - 300, (int)y + 350, 600, 50, BLACK);
	DrawRectangle((int)x - 295, (int)y + 355, (int)(590 * ((float)health/maxHealth)), 40, GREEN);
}