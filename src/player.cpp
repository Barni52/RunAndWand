#include "player.h"

Player::Player(float x, float y, int penetration, float attackSpeed) : Entity(x, y, 30), speed(400), penetration(penetration), 
attackSpeed(attackSpeed), lastShot(0), damage(1) {
	lastShot = GetTime();
}

void Player::shoot(const int mousePosX, const int mousePosY, std::vector<std::unique_ptr<Projectile>>& projectileVector) {
	if (GetTime() - lastShot >= attackSpeed) {
		Projectile projectile(*this, (float)mousePosX, (float)mousePosY, penetration);
		projectileVector.push_back(std::make_unique<Projectile>(projectile));
		lastShot = GetTime();
	}
}

void Player::draw() {
	// Draw the player
	DrawRectangle((int)x, (int)y, (int)width, (int)width, BLUE);
}