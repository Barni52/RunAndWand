#pragma once
#include "raylib.h"	

class TextureLoader{
public:
	Texture2D playerTexture;
	Texture2D enemyTexture1;
	Texture2D projectileTexture1;
	Texture2D grassTexture;

	TextureLoader();
	~TextureLoader();
	bool loadTextures();
};