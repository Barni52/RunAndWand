#pragma once
#include "raylib.h"

class Button {
	int x;
	int y;
	int width;
	int height;
public:
	Button(int x, int y, int width, int height);
	void draw() const;
};