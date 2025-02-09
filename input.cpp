#include "input.h"
#include "raylib.h"
#include "player.h"
#include "middleFinder.h"
#include <iostream>

void handleInput(Player& player) {
	if (IsKeyDown(KEY_W) && player.playerY > 0) {
		player.playerY -= player.speed;
	}

	if (IsKeyDown(KEY_A) && player.playerX > 0) {
		player.playerX -= player.speed;
	}
	if (IsKeyDown(KEY_S) && player.playerY < 1021 * TILE_SIZE) {
		player.playerY += player.speed;
	}

	if (IsKeyDown(KEY_D) && player.playerX < 1021 * TILE_SIZE) {
		player.playerX += player.speed;
	}
}