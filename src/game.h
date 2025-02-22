#pragma once
#include <memory>
#include "projectile.h"
#include "enemy.h"
#include "button.h"
#include "menu.h"
#include "levelUpMenu.h"

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
	bool loadMenu;

	void Reset();

};