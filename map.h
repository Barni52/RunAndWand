#pragma once
#define TILE_SIZE 10 //Defines the size of a tile in pixels
#define CHUNK_SIZE 16 // Defines the chunk size in tiles
#define WORLD_SIZE 1024 // Defines the world size in tiles
#define LOADED_CHUNKS 6 // Defines how many chunks will be loaded in each direction (number of chunks loaded = (LOADED_CHUNKS*2)^2)
#include <memory>
class Player;

class Chunk {
private:
	int chunkX;
	int chunkY;
public:
	Chunk(int chunkX, int chunkY);
	void draw() const;
};

class Map {
private:
	std::unique_ptr<Chunk> chunks[WORLD_SIZE / CHUNK_SIZE][WORLD_SIZE / CHUNK_SIZE];
public:
	Map();
	void loadAndRenderChunks(Player& player);
};
