#include "input.h"
#include "raylib.h"
#include "player.h"
#include "middleFinder.h"
#include <iostream>

void handleInput(Player& player) {
	Vector2 velocity = { 0, 0 };

	if (IsKeyDown(KEY_W) && player.playerY > 0) {
		velocity.y -= 1;;
	}

	if (IsKeyDown(KEY_A) && player.playerX > 0) {
		velocity.x -= 1;;
	}
	if (IsKeyDown(KEY_S) && player.playerY < 1021 * TILE_SIZE) {
		velocity.y += 1;;
	}

	if (IsKeyDown(KEY_D) && player.playerX < 1021 * TILE_SIZE) {
		velocity.x += 1;;
	}

	// Normalize speed when moving diagonally
	if (velocity.x != 0 && velocity.y != 0) {
		velocity.x *= 0.7071f;  // 1/sqrt(2)
		velocity.y *= 0.7071f;
	}

	player.playerX += velocity.x * player.speed;
	player.playerY += velocity.y * player.speed;

	if (player.playerX < 0) {
		player.playerX = 0;
	}

	if (player.playerY < 0) {
		player.playerY = 0;
	}
	if (player.playerX > 1021 * TILE_SIZE) {
		player.playerX = 1021 * TILE_SIZE;
	}
	if (player.playerY > 1021 * TILE_SIZE) {
		player.playerY = 1021 * TILE_SIZE;
	}


}