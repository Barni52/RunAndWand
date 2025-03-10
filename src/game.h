#pragma once
#define RAYLIB_STATIC
#include <memory>
#include "projectile.h"
#include "enemy.h"
#include "button.h"
#include "menu.h"
#include "levelUpMenu.h"
#include "enemyLoader.h"
#include "scoreSave.h"
#include "input.h"
#include <iostream>
#include "projectile.h"
#include <vector>
#include "middleFinder.h"
#include <memory>
#include "enemy.h"
#include "collision.h"
#include "textureLoader.h"
#include "raylib.h"
#include "game.h"
#include "map.h"
#include "player.h"


class Game{
public:
	Game();
	void Run();

	std::vector<std::unique_ptr<Projectile>> projectileVector;
	std::vector<std::unique_ptr<Enemy>> enemyVector;

	Camera2D camera;
	std::vector<Button> buttons;
	Player player;
	Map map;
	Menu menu;
	LevelUpMenu levelUpMenu;
	EnemyLoader enemyLoader;
	ScoreSaver scoreSaver;
	bool loadMenu;
	TextureLoader textureLoader;

	void Reset();

};