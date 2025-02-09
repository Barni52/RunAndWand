#include "raylib.h"
#include "game.h"
#include "map.h"
#include "player.h"
#include "input.h"
#include <iostream>
#include "projectile.h"
#include <vector>
#include "middleFinder.h"

Game::Game() {
	InitWindow(1600, 900, "Raylib Game");
	SetTargetFPS(60);
}
void Game::Run() {
	std::vector<Projectile> projectileVector;
	Player player(0,0);
	Map map = Map();

	Camera2D camera = { 0 };
	camera.target = { player.playerX, player.playerY};
	camera.offset = { 800, 450 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	while (!WindowShouldClose()) {

		//Handle movement inpout from player
		handleInput(player);

		//Handle shooting
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 mousePos = GetMousePosition();
			Projectile p = player.shoot(player, getTileCoordinateX((int)mousePos.x, player.playerX - 1) , getTileCoordinateY((int)mousePos.y, player.playerY - 1));
			projectileVector.push_back(p);
		}

		//Update projectiles
		float deltaTime = GetFrameTime();
		updateProjectiles(projectileVector, deltaTime);

		//Centers the camera to the player
		camera.target = { (float)player.playerX, (float)player.playerY};

		BeginDrawing();

			//Random shit to make raylib happy, no clue what this does
			ClearBackground(RAYWHITE);
			BeginMode2D(camera);

			//Render and update chunks
			map.loadAndRenderChunks(player.playerX, player.playerY);

			//Draw player and random square
			DrawRectangle(300 * TILE_SIZE, 300 * TILE_SIZE, 3 * TILE_SIZE, 3 * TILE_SIZE, GREEN);
			DrawRectangle(player.playerX, player.playerY, 3 * TILE_SIZE, 3 * TILE_SIZE, RED);

			//Draw projectiles
			drawProjectiles(projectileVector);

			DrawFPS(player.playerX, player.playerY + -400);

			EndMode2D();
		EndDrawing();
	}
	CloseWindow();
}