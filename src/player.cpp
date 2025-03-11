#include "player.h"

Player::Player(float x, float y, int penetration, float attackSpeed, Texture2D texture) : Entity(x, y, 30), speed(250), penetration(penetration), 
attackSpeed(attackSpeed), lastShot(0), damage(1), level(1), currentExperience(0), experienceToNextLevel(10), score(0), texture(texture) {
	lastShot = (float)GetTime();
}

void Player::shoot(const int mousePosX, const int mousePosY, std::vector<std::unique_ptr<Projectile>>& projectileVector, TextureLoader& textureLoader) {
	if (GetTime() - lastShot >= attackSpeed) {
		Projectile projectile(*this, (float)mousePosX, (float)mousePosY, penetration, textureLoader.projectileTexture1);
		projectileVector.push_back(std::make_unique<Projectile>(projectile));
		lastShot = (float)GetTime();
	}
}

Player::Player() : Entity(x, y, 30) {
}

void Player::draw() {
	// Draw the player
	//DrawRectangle((int)x, (int)y, (int)width, (int)width, BLUE);

	float scale = 0.60f;
	float adjustX = 8.0f;
	float adjustY = 10.0f;

	Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
	Rectangle dest = { (float)(int)x, (float)(int)y, texture.width * scale, texture.height * scale };

	// Start with the center of the texture as the origin
	Vector2 origin = { (texture.width * scale) / 2, (texture.height * scale) / 2 };

	origin.x -= adjustX;
	origin.y -= adjustY;

	DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}