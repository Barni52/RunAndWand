#include "textureLoader.h"
#include <stdio.h>
#include <iostream>

TextureLoader::TextureLoader() {}

TextureLoader::~TextureLoader() {
	UnloadTexture(playerTexture);
	UnloadTexture(enemyTexture1);
	UnloadTexture(projectileTexture1);
	UnloadTexture(grassTexture);
}

bool TextureLoader::loadTextures() {
	playerTexture = LoadTexture("../resources/player.png");
	enemyTexture1 = LoadTexture("../resources/enemy1.png");
	projectileTexture1 = LoadTexture("../resources/projectile1.png");
	grassTexture = LoadTexture("../resources/grass.png");

	Image icon = LoadImage("resources/RAWicon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);
	
	return true;
}
