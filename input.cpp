#include "input.h"
#include "raylib.h"
#include "player.h"
#include "middleFinder.h"
#include <iostream>

void handleInput(Player& player) {
	Vector2 velocity = { 0, 0 };

	if (IsKeyDown(KEY_W) && player.y > 0) {
		velocity.y -= 1;;
	}

	if (IsKeyDown(KEY_A) && player.x > 0) {
		velocity.x -= 1;;
	}
	if (IsKeyDown(KEY_S) && player.y < 1021 * TILE_SIZE) {
		velocity.y += 1;;
	}

	if (IsKeyDown(KEY_D) && player.x < 1021 * TILE_SIZE) {
		velocity.x += 1;;
	}

	// Normalize speed when moving diagonally
	if (velocity.x != 0 && velocity.y != 0) {
		velocity.x *= 0.7071f;  // 1/sqrt(2)
		velocity.y *= 0.7071f;
	}

	player.x += velocity.x * player.speed;
	player.y += velocity.y * player.speed;

	if (player.x < 0) {
		player.x = 0;
	}

	if (player.y < 0) {
		player.y = 0;
	}
	if (player.x > 1021 * TILE_SIZE) {
		player.x = 1021 * TILE_SIZE;
	}
	if (player.y > 1021 * TILE_SIZE) {
		player.y = 1021 * TILE_SIZE;
	}


}