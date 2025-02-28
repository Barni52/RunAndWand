#include "LevelUpMenu.h"
#include <iostream>
#include <string>

LevelUpMenu::LevelUpMenu() {

};

bool LevelUpMenu::draw(Player& player) const {

    while (!WindowShouldClose()) {

        int buttonWidth = 300;
        int buttonHeight = 120;

        Rectangle button1 = {
            GetScreenWidth() * 0.25f - buttonWidth / 2.0f,
            GetScreenHeight() / 2.0f - buttonHeight / 2.0f,
            (float)buttonWidth, (float)buttonHeight
        };

        Rectangle button2 = {
            GetScreenWidth() * 0.50f - buttonWidth / 2.0f,
            GetScreenHeight() / 2.0f - buttonHeight / 2.0f,
            (float)buttonWidth, (float)buttonHeight
        };

        Rectangle button3 = {
            GetScreenWidth() * 0.75f - buttonWidth / 2.0f,
            GetScreenHeight() / 2.0f - buttonHeight / 2.0f,
            (float)buttonWidth, (float)buttonHeight
        };

        BeginDrawing();

        Vector2 mousePoint = GetMousePosition();
        bool hovered1 = hasCollided(button1, mousePoint);
        bool hovered2 = hasCollided(button2, mousePoint);
        bool hovered3 = hasCollided(button3, mousePoint);

        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Button color changes when hovered

        DrawRectangleRec(button1, hovered1 ? GRAY : LIGHTGRAY);
        DrawRectangleLinesEx(button1, 3, BLACK);

        DrawRectangleRec(button2, hovered2 ? GRAY : LIGHTGRAY);
        DrawRectangleLinesEx(button2, 3, BLACK);

        DrawRectangleRec(button3, hovered3 ? GRAY : LIGHTGRAY);
        DrawRectangleLinesEx(button3, 3, BLACK);

        // Button text
		std::string s = "Attack Speed";
        DrawText(s.c_str(),
            (int)(button1.x + button1.width / 2 - MeasureText("Attack Speed", 30) / 2),
            (int)(button1.y + button1.height / 2 - 30 / 2),
            30, BLACK);

        DrawText("Speed",
            (int)(button2.x + button2.width / 2 - MeasureText("Speed", 30) / 2),
            (int)(button2.y + button2.height / 2 - 30 / 2),
            30, BLACK);

        DrawText("Penetration",
            (int)(button3.x + button3.width / 2 - MeasureText("Penetration", 30) / 2),
            (int)(button3.y + button3.height / 2 - 30 / 2),
            30, BLACK);

        // Detect button click
        if (hovered1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			player.attackSpeed *= 0.9f;
            return true;
        } else if(hovered2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            player.speed *= 1.1f;
            return true;
		} else if (hovered3 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            player.penetration++;
            return true;
		}



        EndDrawing();
    };
    return false;
};
