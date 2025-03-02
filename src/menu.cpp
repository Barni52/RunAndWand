#include "menu.h"

Menu::Menu() {

};

bool Menu::draw(int highscore) const {

	while (!WindowShouldClose()) {

        int buttonWidth = 200;
        int buttonHeight = 80;
        Rectangle startButton = {
            GetScreenWidth() / 2.0f - buttonWidth / 2.0f,
            GetScreenHeight() / 2.0f - buttonHeight / 2.0f,
            (float)buttonWidth, (float)buttonHeight
        };

		BeginDrawing();
        Vector2 mousePoint = GetMousePosition();
        bool hovered = hasCollided(startButton, mousePoint);

        // Draw
        BeginDrawing();
            ClearBackground(DARKGRAY);

            // Button color changes when hovered
            Color buttonColor = hovered ? GRAY : LIGHTGRAY;
            DrawRectangleRec(startButton, buttonColor);
            DrawRectangleLinesEx(startButton, 3, BLACK);

            // Button text
            DrawText("START", (int)(startButton.x + buttonWidth / 4), (int)(startButton.y + buttonHeight / 4), 30, BLACK);

            //High Score text
			std::string s = "High Score: " + std::to_string(highscore);
			DrawText(s.c_str(), (int)(startButton.x + buttonWidth / 4), (int)(startButton.y + buttonHeight / 4) - 200, 30, BLACK);

            // Detect button click
            if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                return true;
            }


		EndDrawing();
	};
	return false;
};