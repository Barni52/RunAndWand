#include "map.h"

int getTileCoordinateX(int mousePosX, int playerX) {
	int tile = ((mousePosX - 800) / TILE_SIZE) + playerX;
	return tile;
}
int getTileCoordinateY(int mousePosY, int playerY) {
	int tile = ((mousePosY - 450) / TILE_SIZE) + playerY;
	return tile;
}