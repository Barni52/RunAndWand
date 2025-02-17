#pragma once
#include <memory>
#include "projectile.h"
#include "enemy.h"
#include "button.h"
#include "menu.h"

class Game{
public:
	Game();
	void Run();

	std::vector<std::unique_ptr<Projectile>> projectileVector;
	std::vector<std::unique_ptr<Enemy>> enemyVector;
	std::vector<Button> buttons;
	Player player;
	Map map;
	Menu menu;
	bool loadMenu;

	void Reset();

};