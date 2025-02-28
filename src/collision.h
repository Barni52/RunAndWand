#pragma once

#include "entity.h"
#include "projectile.h"
#include "enemy.h"
#include <vector>
#include <memory>
#include "raylib.h"

bool hasCollided(const Entity& e1, const Entity& e2);
bool hasCollided(const Entity& e1, int x, int y);
bool hasCollided(Rectangle r1, Rectangle r2);
bool hasCollided(Rectangle r1, Vector2);

void killEnemies(std::vector<std::unique_ptr<Projectile>>& projectileVector, std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player);
bool hitPlayer(Player& player, std::vector<std::unique_ptr<Enemy>>& enemyVector);