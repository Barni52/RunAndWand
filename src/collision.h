#pragma once

#include "entity.h"
#include "projectile.h"
#include "enemy.h"
#include <vector>
#include <memory>

bool hasCollided(const Entity& e1, const Entity& e2);
bool hasCollided(const Entity& e1, int x, int y);

void killEnemies(std::vector<std::unique_ptr<Projectile>>& projectileVector, std::vector<std::unique_ptr<Enemy>>& enemyVector);
bool hitPlayer(Player& player, std::vector<std::unique_ptr<Enemy>>& enemyVector);