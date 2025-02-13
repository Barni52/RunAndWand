#pragma once

#include "entity.h"
#include "projectile.h"
#include "enemy.h"
#include <vector>
#include <memory>

bool hasCollided(const Entity& e1, const Entity& e2);

void killEnemies(std::vector<std::unique_ptr<Projectile>>& projectileVector, std::vector<std::unique_ptr<Enemy>>& enemyVector);
void hitPlayer(Player& player, std::vector<std::unique_ptr<Enemy>>& enemyVector);