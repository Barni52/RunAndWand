#include "raylib.h"
#include "game.h"
#include "map.h"

Game::Game() {
	InitWindow(1600, 900, "Raylib Game");
	SetTargetFPS(60);
}
void Game::Run() {
	int playerX = 0;
	int playerY = 0;
	Map map = Map();

	Camera2D camera = { 0 };
	camera.target = { (float)playerX * TILE_SIZE, (float)playerY * TILE_SIZE };
	camera.offset = { 800, 450 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_W) && playerY > 0) {
			playerY--;
		}

		if (IsKeyDown(KEY_A) && playerX > 0) {
			playerX--;
		}
		if (IsKeyDown(KEY_S) && playerY < 1024) {
			playerY++;
		}

		if (IsKeyDown(KEY_D) && playerX < 1024) {
			playerX++;
		}

		camera.target = { (float)playerX * TILE_SIZE, (float)playerY * TILE_SIZE };

		BeginDrawing();
			ClearBackground(RAYWHITE);
			BeginMode2D(camera);
			map.loadAndRenderChunks(playerX, playerY);
			DrawRectangle(300 * TILE_SIZE, 300 * TILE_SIZE, 3 * TILE_SIZE, 3 * TILE_SIZE, GREEN);
			DrawRectangle(playerX * TILE_SIZE, playerY * TILE_SIZE, 3 * TILE_SIZE, 3 * TILE_SIZE, RED);

			DrawFPS(playerX * TILE_SIZE, playerY * TILE_SIZE + -400);

			EndMode2D();
		EndDrawing();
	}
	CloseWindow();
}