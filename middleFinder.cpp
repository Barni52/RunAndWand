#include "map.h"

int getTileCoordinateX(const int mousePosX, const int playerX) {
	int tile = ((mousePosX - 800) / TILE_SIZE) + playerX;
	return tile;
}
int getTileCoordinateY(const int mousePosY, const int playerY) {
	int tile = ((mousePosY - 450) / TILE_SIZE) + playerY;
	return tile;
}