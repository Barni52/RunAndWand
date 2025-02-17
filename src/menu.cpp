#include "menu.h"
#include "collision.h"
#include <iostream>

Menu::Menu() {

};

bool Menu::draw(int screenWidth, int screenHeight) const {

    int buttonWidth = 200;
    int buttonHeight = 80;
    Rectangle startButton = {
        screenWidth / 2.0f - buttonWidth / 2.0f,
        screenHeight / 2.0f - buttonHeight / 2.0f,
        (float)buttonWidth, (float)buttonHeight
    };
	Entity startEntity = Entity(startButton.x, startButton.y, buttonWidth);

	while (!WindowShouldClose()) {
		BeginDrawing();

			
            

            Vector2 mousePoint = GetMousePosition();
            bool hovered = hasCollided(startEntity, mousePoint.x, mousePoint.y);

            // Draw
            BeginDrawing();
            ClearBackground(DARKGRAY);

            // Button color changes when hovered
            Color buttonColor = hovered ? GRAY : LIGHTGRAY;
            DrawRectangleRec(startButton, buttonColor);
            DrawRectangleLinesEx(startButton, 3, BLACK);

            // Button text
            DrawText("START", startButton.x + buttonWidth / 4, startButton.y + buttonHeight / 4, 30, BLACK);

            // Detect button click
            if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                return true;
            }


		EndDrawing();
	};
	return false;
};