#include "LevelUpMenu.h"
#include <iostream>

LevelUpMenu::LevelUpMenu() {

};

bool LevelUpMenu::draw(int screenWidth, int screenHeight) const {

    int buttonWidth = 300;
    int buttonHeight = 120;

    Rectangle attackSpeedButton = {
        screenWidth * 0.25f - buttonWidth / 2.0f,
        screenHeight / 2.0f - buttonHeight / 2.0f,
        (float)buttonWidth, (float)buttonHeight
    };

    Rectangle speedButton = {
        screenWidth * 0.50f - buttonWidth / 2.0f,
        screenHeight / 2.0f - buttonHeight / 2.0f,
        (float)buttonWidth, (float)buttonHeight
    };

    Rectangle penetrationButton = {
        screenWidth * 0.75f - buttonWidth / 2.0f,
        screenHeight / 2.0f - buttonHeight / 2.0f,
        (float)buttonWidth, (float)buttonHeight
    };

    while (!WindowShouldClose()) {
        BeginDrawing();

        Vector2 mousePoint = GetMousePosition();
        bool hovered1 = hasCollided(attackSpeedButton, mousePoint);
        bool hovered2 = hasCollided(speedButton, mousePoint);
        bool hovered3 = hasCollided(penetrationButton, mousePoint);

        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Button color changes when hovered

        DrawRectangleRec(attackSpeedButton, hovered1 ? GRAY : LIGHTGRAY);
        DrawRectangleLinesEx(attackSpeedButton, 3, BLACK);

        DrawRectangleRec(speedButton, hovered2 ? GRAY : LIGHTGRAY);
        DrawRectangleLinesEx(speedButton, 3, BLACK);

        DrawRectangleRec(penetrationButton, hovered3 ? GRAY : LIGHTGRAY);
        DrawRectangleLinesEx(penetrationButton, 3, BLACK);

        // Button text
        DrawText("Attack Speed",
            (int)(attackSpeedButton.x + attackSpeedButton.width / 2 - MeasureText("Attack Speed", 30) / 2),
            (int)(attackSpeedButton.y + attackSpeedButton.height / 2 - 30 / 2),
            30, BLACK);

        DrawText("Speed",
            (int)(speedButton.x + speedButton.width / 2 - MeasureText("Speed", 30) / 2),
            (int)(speedButton.y + speedButton.height / 2 - 30 / 2),
            30, BLACK);

        DrawText("Penetration",
            (int)(penetrationButton.x + penetrationButton.width / 2 - MeasureText("Penetration", 30) / 2),
            (int)(penetrationButton.y + penetrationButton.height / 2 - 30 / 2),
            30, BLACK);

        // Detect button click
        if (hovered1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			std::cout << "Attack speed" << std::endl;
            return true;
        } else if(hovered2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			std::cout << "Speed" << std::endl;
            return true;
		} else if (hovered3 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			std::cout << "Penetration" << std::endl;
            return true;
		}



        EndDrawing();
    };
    return false;
};