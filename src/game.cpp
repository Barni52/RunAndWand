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


Game::Game() : player(Player(100, 100, 1, 1.0f)), map(Map()){
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1600, 900, "Run and Wand");
	SetTargetFPS(120);
	Image icon = LoadImage("resources/RAWicon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);


	Camera2D camera = { 0 };
	camera.target = { floor(player.x), floor(player.y) };
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f * ((GetScreenWidth() / 1600) * (GetScreenHeight() / 900));

	projectileVector = std::vector<std::unique_ptr<Projectile>>();
	enemyVector = std::vector<std::unique_ptr<Enemy>>();
	levelUpMenu = LevelUpMenu();
	enemyLoader = EnemyLoader();
	menu = Menu();
	loadMenu = true;
	scoreSaver = ScoreSaver();

}

void Game::Run() { 
	bool stop = false;

	while (!WindowShouldClose()) {

		//Draws the menu, but only once
		if (loadMenu) {
			loadMenu = false;
			if (!menu.draw(scoreSaver.highScore)) {
				return;
			}

			//Ugly hack to stop player from shooting when the game starts instantly
			player.lastShot = (float)GetTime();
		}


		//Spawns enemies
		enemyLoader.loadEnemies(enemyVector, player);
		if (player.currentExperience > player.experienceToNextLevel || IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) {
			player.currentExperience = player.currentExperience - player.experienceToNextLevel;
			player.experienceToNextLevel = player.experienceToNextLevel * 1.25;

			if (!levelUpMenu.draw(player)) {
				return;
			}

			//Ugly hack to stop player from shooting when the game starts instantly
			player.lastShot = (float)GetTime();
			
			//Logs the stats of the player
			std::cout << "Player stats: " << std::endl;
			std::cout << "Player attackSpeed: " << player.attackSpeed << std::endl;
			std::cout << "Player speed: " << player.speed << std::endl;
			std::cout << "Player penetration: " << player.penetration << std::endl;
			std::cout << "Player damage: " << player.damage << std::endl;
		}

		//Zooms when the screen gets too big, so bigger res doesnt give that big of an advantage
		if (GetScreenWidth() > 1800 || GetScreenHeight() > 1200) {
			camera.zoom = 1.5f;
		} else {
			camera.zoom = 1.0f;
		}

		//Handle movement input from player
		handleInput(player);

		//Handle clicking : pressing buttons, and shooting
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 mousePos = GetMousePosition();

			//Calculates where the mouse is by, taking its position on the screen and adds it to the player coordinate which is always centered
			//The -1 is needed so that the projectile spawns from the middle of the player instead of its upper left corner
			int targetX = (int)(((mousePos.x - GetScreenWidth() / 2.0f) / TILE_SIZE) + player.x - 1);
			int targetY = (int)(((mousePos.y - GetScreenHeight() / 2.0f) / TILE_SIZE) + player.y - 1);
			player.shoot(targetX, targetY, projectileVector);
		}

		//Update projectiles
		float deltaTime = GetFrameTime();
		updateProjectiles(projectileVector, deltaTime);

		//Update enemies
		//Also stops enemies if p is pressed (debug)
		if (IsKeyPressed(KEY_P)) {
			stop = !stop;
			std::cout << "Enemies stopped: " << stop << std::endl;
		}

		if (!stop) {
			updateEnemies(enemyVector, deltaTime, player);
			killEnemies(projectileVector, enemyVector, player);
			if (hitPlayer(player, enemyVector)) {
				scoreSaver.saveHighScore(player.score);
				if (!menu.draw(scoreSaver.highScore)) {
					return;
				}
				else {
					Reset();
				}
			}
		}

		

		//Centers the camera to the player
		camera.target = { floor(player.x), floor(player.y) };
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
	player = Player(100, 100, 1, 1.0f);
	enemyLoader = EnemyLoader();
}