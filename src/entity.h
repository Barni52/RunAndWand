#pragma once

class Entity {
public:
	static int idCounter;

	int id;

	float x;
	float y;
	float width;

	Entity(float x, float y, float width);
};
