#include "raylib.h"
#include "map.h"
#include <iostream>
#include "player.h"


//Chunk x,y is the chunk's coordinate in the world
Chunk::Chunk(int chunkX, int chunkY, Texture2D texture) : chunkX(chunkX), chunkY(chunkY), texture(texture) {}

void Chunk::draw() const{
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			int worldX = (chunkX * CHUNK_SIZE + x) * TILE_SIZE;
			int worldY = (chunkY * CHUNK_SIZE + y) * TILE_SIZE;
			//DrawRectangle(worldX, worldY, TILE_SIZE, TILE_SIZE, ((x + y) % 2 == 0) ? DARKGRAY : GRAY);
		}
	}

	Rectangle sourceRect = { 0, 0, (float)texture.width, (float)texture.height };
	Rectangle destRect = { (float)(chunkX * CHUNK_SIZE) * TILE_SIZE, (float)(chunkY * CHUNK_SIZE) * TILE_SIZE, (float)CHUNK_SIZE * TILE_SIZE, (float)CHUNK_SIZE * TILE_SIZE};

	DrawTexturePro(texture, sourceRect, destRect, { 0, 0 }, 0.0f, WHITE);
}

Map::Map(TextureLoader& textureLoader) {
	textureLoader = textureLoader;
	for (int x = 0; x < WORLD_SIZE / CHUNK_SIZE; x++) {
		for (int y = 0; y < WORLD_SIZE / CHUNK_SIZE; y++) {
			chunks[x][y] = std::make_unique<Chunk>(x, y, textureLoader.grassTexture);
		}
	}
}

Map::Map() {}

void Map::loadAndRenderChunks(Player& player) {

	int playerChunkX = (int)player.x / CHUNK_SIZE / TILE_SIZE;
	int playerChunkY = (int)player.y / CHUNK_SIZE / TILE_SIZE;
	for (int x = playerChunkX - LOADED_CHUNKS; x < playerChunkX + LOADED_CHUNKS; x++) {
		for (int y = playerChunkY - LOADED_CHUNKS; y < playerChunkY + LOADED_CHUNKS; y++) {
			if (x >= 0 && y >= 0 && x < WORLD_SIZE / CHUNK_SIZE && y < WORLD_SIZE / CHUNK_SIZE) {
				chunks[x][y]->draw();
			}
		}
	}
}