#include "entity.h"

int Entity::idCounter = 0;

Entity::Entity(float x, float y, float width) : x(x), y(y), width(width), id(idCounter){
	idCounter++;
};