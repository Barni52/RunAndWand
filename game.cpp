#include "raylib.h"
#include "game.h"
#include "map.h"
#include "player.h"
#include "input.h"
#include <iostream>
#include "projectile.h"
#include <vector>
#include "middleFinder.h"
#include <memory>
#include "enemy.h"

Game::Game() {
	InitWindow(1600, 900, "Raylib Game");
	SetTargetFPS(60);
}
void Game::Run() {
	std::vector<std::unique_ptr<Projectile>> projectileVector;
	std::vector<std::unique_ptr<Enemy>> enemyVector;
	Player player(100, 100);
	Map map = Map();

	Camera2D camera = { 0 };
	camera.target = { player.x, player.y};
	camera.offset = { 800, 450 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	//test
	Enemy e(0, 400);
	enemyVector.push_back(std::make_unique<Enemy>(e));
	//

	while (!WindowShouldClose()) {

		//Handle movement inpout from player
		handleInput(player);

		//Handle shooting
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 mousePos = GetMousePosition();
			Projectile p = player.shoot(player, getTileCoordinateX((int)mousePos.x, (int)player.x - 1) , getTileCoordinateY((int)mousePos.y, (int)player.y - 1));
			projectileVector.push_back(std::make_unique<Projectile>(p));
		}

		//Update projectiles
		float deltaTime = GetFrameTime();
		updateProjectiles(projectileVector, deltaTime);

		//Update enemies
		updateEnemies(enemyVector, deltaTime, player);

		//Centers the camera to the player
		camera.target = { (float)player.x, (float)player.y};

		BeginDrawing();

			//Random shit to make raylib happy, no clue what this does
			ClearBackground(RAYWHITE);
			BeginMode2D(camera);

			//Render and update chunks
			map.loadAndRenderChunks(player);

			//Draw player and random square
			DrawRectangle(300 * TILE_SIZE, 300 * TILE_SIZE, 3 * TILE_SIZE, 3 * TILE_SIZE, GREEN);
			player.draw();

			//Render enemies
			drawEnemies(enemyVector);

			//Draw projectiles
			drawProjectiles(projectileVector);

			DrawFPS((int)player.x, (int)player.y + -400);

			EndMode2D();
		EndDrawing();
	}
	CloseWindow();
}