#include "collision.h"
#include <vector>
#include <memory>
#include <iostream>


bool hasCollided(const Entity& e1, const Entity& e2) {
	if (
		e1.x <= e2.x + e2.width &&
		e1.x + e1.width >= e2.x &&
		e1.y <= e2.y + e2.width &&
		e1.y + e1.width >= e2.y
		) {
		return true;
		} else {
		return false;
	}
}

void killEnemies(std::vector<std::unique_ptr<Projectile>>& projectileVector, std::vector<std::unique_ptr<Enemy>>& enemyVector) {
	for (std::unique_ptr<Projectile>& pp : projectileVector) {
		for (std::unique_ptr<Enemy>& ep: enemyVector) {
			if (hasCollided(*pp, *ep)) {
				ep->keepAlive = false;
				pp->keepAlive = false;
			}
		}
	}
}

void hitPlayer(Player& player, std::vector<std::unique_ptr<Enemy>>& enemyVector) {
	for (std::unique_ptr<Enemy>& ep : enemyVector) {
		if (hasCollided(player, *ep)) {
			std::cout << "You lost" << std::endl;
		}
	}
}