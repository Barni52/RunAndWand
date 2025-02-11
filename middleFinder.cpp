#include "map.h"

int getTileCoordinateX(const int mousePosX, const int x) {
	int tile = ((mousePosX - 800) / TILE_SIZE) + x;
	return tile;
}
int getTileCoordinateY(const int mousePosY, const int y) {
	int tile = ((mousePosY - 450) / TILE_SIZE) + y;
	return tile;
}