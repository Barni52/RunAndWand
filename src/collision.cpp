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

//for mouse click detection
bool hasCollided(const Entity& e1, int x, int y) {
	if (
		e1.x <= x + 1 &&
		e1.x + e1.width >= x &&
		e1.y <= y + 1 &&
		e1.y + e1.width >= y
		) {
		return true;
	}
	else {
		return false;
	}
}

bool hasCollided(Rectangle r1, Rectangle r2) {
	if (
		r1.x <= r2.x + r2.width &&
		r1.x + r1.width >= r2.x &&
		r1.y <= r2.y + r2.height &&
		r1.y + r1.height >= r2.y
		) {
		return true;
	}
	else {
		return false;
	}
}

bool hasCollided(Rectangle r1, Vector2 v) {
	if (
		r1.x <= v.x + 1 &&
		r1.x + r1.width >= v.x &&
		r1.y <= v.y + 1 &&
		r1.y + r1.height >= v.y
		) {
		return true;
	}
	else {
		return false;
	}
}

void killEnemies(std::vector<std::unique_ptr<Projectile>>& projectileVector, std::vector<std::unique_ptr<Enemy>>& enemyVector, const Player& player) {
	for (std::unique_ptr<Projectile>& pp : projectileVector) {
		for (std::unique_ptr<Enemy>& ep: enemyVector) {
			if (hasCollided(*pp, *ep)) {

				pp->penetration--;
				if (pp->penetration <= 0) {
					pp->keepAlive = false;
				}

				//If the enemy has already been shot by this projectile, skip 

				if (!pp->shotEnemyIdSet.contains(ep->id)) {
					ep->currentHealth -= player.damage;
					pp->shotEnemyIdSet.insert(ep->id);
				}
	
				if (ep->currentHealth <= 0) {
					ep->keepAlive = false;
				}
				
					
				//This break is necessary, otherwise the projectile will kill all enemies it collides with
				break;
			}
		}
	}
}

bool hitPlayer(Player& player, std::vector<std::unique_ptr<Enemy>>& enemyVector) {
	for (std::unique_ptr<Enemy>& ep : enemyVector) {
		if (hasCollided(player, *ep)) {
			return true;
		}
	}
	return false;
}