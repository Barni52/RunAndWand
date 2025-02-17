#include "button.h"

Button::Button(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {};

void Button::draw() const {
	DrawRectangle(x, y, width, height, RED);
};