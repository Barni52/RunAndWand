#define RAYLIB_STATIC
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
#include "collision.h"

Game::Game() : player(Player(100, 100)), map(Map()){
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1600, 900, "Run and Wand");
	SetTargetFPS(60);
	Image icon = LoadImage("resources/RAWicon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	projectileVector = std::vector<std::unique_ptr<Projectile>>();
	enemyVector = std::vector<std::unique_ptr<Enemy>>();
	menu = Menu();
	loadMenu = true;
}

void Game::Run() { 

	Camera2D camera = { 0 };
	camera.target = { player.x, player.y};
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f * ((GetScreenWidth() / 1600) * (GetScreenHeight() / 900));

	//test
	enemyVector.push_back(std::make_unique<Enemy>(Enemy(0, 400)));
	//
	int count = 0;

	while (!WindowShouldClose()) {
		if (loadMenu) {
			loadMenu = false;
			if (!menu.draw(GetScreenWidth(), GetScreenHeight())) {
				return;
			}
		}

		//Zooms when the screen gets too big, so bigger res doesnt give that big of an advantage
		if (GetScreenWidth() > 1800 || GetScreenHeight() > 1200) {
			camera.zoom = 1.5f;
		}
		else {
			camera.zoom = 1.0f;
		}
		/*count++;
		if (count >= 100) {
			count = 0;
			enemyVector.push_back(std::make_unique<Enemy>(Enemy(player.x + 700, player.y)));
			enemyVector.push_back(std::make_unique<Enemy>(Enemy(player.x - 700, player.y)));
			enemyVector.push_back(std::make_unique<Enemy>(Enemy(player.x, player.y - 700)));
			enemyVector.push_back(std::make_unique<Enemy>(Enemy(player.x, player.y + 700)));
		}*/



		//Handle movement input from player
		handleInput(player);

		//Handle clicking : pressing buttons, and shooting
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 mousePos = GetMousePosition();

			//Calculates where the mouse is by, taking its position on the screen and adds it to the player coordinate which is always centered
			//The -1 is needed so that the projectile spawns from the middle of the player instead of its upper left corner
			int targetX = (int)(((mousePos.x - GetScreenWidth() / 2.0f) / TILE_SIZE) + player.x - 1);
			int targetY = (int)(((mousePos.y - GetScreenHeight() / 2.0f) / TILE_SIZE) + player.y - 1);
			Projectile p = player.shoot(targetX, targetY);
			projectileVector.push_back(std::make_unique<Projectile>(p));
		}

		//Update projectiles
		float deltaTime = GetFrameTime();
		updateProjectiles(projectileVector, deltaTime);

		//Update enemies
		updateEnemies(enemyVector, deltaTime, player);
		killEnemies(projectileVector, enemyVector);
		if (hitPlayer(player, enemyVector)) {
			if (!menu.draw(GetScreenWidth(), GetScreenHeight())) {
				return;
			} else {
				Reset();
			}
		}

		//Centers the camera to the player
		camera.target = { (float)player.x, (float)player.y};
		camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

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

void Game::Reset() {
	projectileVector = std::vector<std::unique_ptr<Projectile>>();
	enemyVector = std::vector<std::unique_ptr<Enemy>>();
	player = Player(100, 100);
}

void menuRender() {

}