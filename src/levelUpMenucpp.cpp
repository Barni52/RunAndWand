#include "LevelUpMenu.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <functional>
#include <unordered_set>


enum rarity {
    common,
	uncommon,
    rare,
    epic,
    legendary,
	mythic
};

enum upgrade {
    attackSpeed,
    speed,
    penetration,
    damage
};

static std::vector<rarity> getRandomRarities() {
    std::vector<rarity> selectionPool;

    for (int i = 0; i < 100; i++) selectionPool.push_back(common);
    for (int i = 0; i < 50; i++) selectionPool.push_back(uncommon);
    for (int i = 0; i < 30; i++) selectionPool.push_back(rare);
    for (int i = 0; i < 15; i++) selectionPool.push_back(epic);
    for (int i = 0; i < 5; i++) selectionPool.push_back(legendary);
    for (int i = 0; i < 1; i++) selectionPool.push_back(mythic);


    std::vector<rarity> result;
    for (int i = 0; i < 3; i++) {
        int index = std::rand() % selectionPool.size();
        result.push_back(selectionPool[index]);
    }

    return result;
}


static std::vector<upgrade> getRandomUpgrades() {
    std::vector<upgrade> selectionPool;

    for (int i = 0; i < 10; i++) selectionPool.push_back(attackSpeed);
    for (int i = 0; i < 20; i++) selectionPool.push_back(speed);
    for (int i = 0; i < 11; i++) selectionPool.push_back(penetration);
    for (int i = 0; i < 1; i++) selectionPool.push_back(damage);

    std::vector<upgrade> result;
    std::unordered_set<upgrade> selected;

    while (result.size() < 3) {
        int index = std::rand() % selectionPool.size();

        if (selected.insert(selectionPool[index]).second) {
            result.push_back(selectionPool[index]);
        }
    }

    return result;
}


std::string getStringFromUpgrade(upgrade upgrade, rarity rarity) {
	std::string result = "";

	switch (upgrade) {
	case attackSpeed:
		result = "Attack speed";
		break;
	case speed:
		result = "Speed";
		break;
	case penetration:
		result = "Penetration";
		break;
	case damage:
		result = "Damage";
		break;
	}

    switch (rarity) {
	case common:
		result += " (Common)";
		break;
    case uncommon:
		result += " (Uncommon)";
		break;
	case rare:
		result += " (Rare)";
		break;
	case epic:
		result += " (Epic)";
		break;
	case legendary:
		result += " (Legendary)";
		break;
	case mythic:
		result += " (Mythic)";
		break;
    }
    return result;
}

static void upgradeAttackSpeed(Player& player, float modifier) {
	player.attackSpeed *= 0.9f;
}

static void upgradeSpeed(Player& player, float modifier) {
	player.speed *= 1.1f;
}

static void upgradePenetration(Player& player, float modifier) {
	player.penetration++;
}

static void upgradeDamage(Player& player, float modifier) {
	player.damage++;
}


void attachUpgrade(std::function<void(Player& player, float modifier)>& upgradeFunc, upgrade upgrade) {
    switch (upgrade) {
    case attackSpeed:
        upgradeFunc = upgradeAttackSpeed;
        break;
    case speed:
        upgradeFunc = upgradeSpeed;
        break;
    case penetration:
        upgradeFunc = upgradePenetration;
        break;
    case damage:
        upgradeFunc = upgradeDamage;
        break;
    }
}

LevelUpMenu::LevelUpMenu() {

};

bool LevelUpMenu::draw(Player& player) const {

    std::function<void(Player& player, float modifier)> upgradeFunc1;
    std::function<void(Player& player, float modifier)> upgradeFunc2;
    std::function<void(Player& player, float modifier)> upgradeFunc3;

    std::vector<rarity> rarities = getRandomRarities();
    std::vector<upgrade> upgrades = getRandomUpgrades();

	attachUpgrade(upgradeFunc1, upgrades[0]);
	attachUpgrade(upgradeFunc2, upgrades[1]);
	attachUpgrade(upgradeFunc3, upgrades[2]);

    std::string s1 = getStringFromUpgrade(upgrades[0], rarities[0]);
    std::string s2 = getStringFromUpgrade(upgrades[1], rarities[1]);
    std::string s3 = getStringFromUpgrade(upgrades[2], rarities[2]);

    while (!WindowShouldClose()) {

        int buttonWidth = 400;
        int buttonHeight = 160;

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
            DrawText(s1.c_str(),
                (int)(button1.x + button1.width / 2 - MeasureText(s1.c_str(), 30) / 2),
                (int)(button1.y + button1.height / 2 - 30 / 2),
                30, BLACK);

            DrawText(s2.c_str(),
                (int)(button2.x + button2.width / 2 - MeasureText(s2.c_str(), 30) / 2),
                (int)(button2.y + button2.height / 2 - 30 / 2),
                30, BLACK);

            DrawText(s3.c_str(),
                (int)(button3.x + button3.width / 2 - MeasureText(s3.c_str(), 30) / 2),
                (int)(button3.y + button3.height / 2 - 30 / 2),
                30, BLACK);

        EndDrawing();

        // Detect button click
        if (hovered1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			upgradeFunc1(player, 1.0f);
            return true;
        }
        else if (hovered2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            upgradeFunc2(player, 1.0f);
            return true;
        }
        else if (hovered3 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            upgradeFunc3(player, 1.0f);
            return true;
        }
    };
    return false;
};

