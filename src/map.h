#pragma once
#define TILE_SIZE 10 //Defines the size of a tile in pixels
#define CHUNK_SIZE 16 // Defines the chunk size in tiles
#define WORLD_SIZE 1024 // Defines the world size in tiles
#define LOADED_CHUNKS 7 // Defines how many chunks will be loaded in each direction (number of chunks loaded = (LOADED_CHUNKS*2)^2)
#define CHUNK_NUMBER WORLD_SIZE / CHUNK_SIZE
#include <memory>
#include <array>
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
	//This disgusting piece of shit here is a 2d array with chunk pointers (please kill it)
	std::array<std::array<std::unique_ptr<Chunk>, CHUNK_NUMBER>, CHUNK_NUMBER> chunks;
public:
	Map();
	void loadAndRenderChunks(Player& player);
};
