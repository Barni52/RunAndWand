#include "input.h"
#include "raylib.h"
#include "player.h"
#include "middleFinder.h"
#include <iostream>

void handleInput(Player& player) {
	if (IsKeyDown(KEY_W) && player.playerY > 0) {
		player.playerY--;
	}

	if (IsKeyDown(KEY_A) && player.playerX > 0) {
		player.playerX--;
	}
	if (IsKeyDown(KEY_S) && player.playerY < 1021) {
		player.playerY++;
	}

	if (IsKeyDown(KEY_D) && player.playerX < 1021) {
		player.playerX++;
	}
}