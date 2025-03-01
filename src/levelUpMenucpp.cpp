#include "LevelUpMenu.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <functional>
#include <unordered_set>

#include "upgradeDefines.h"


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

    for (int i = 0; i < commonWeight; i++) selectionPool.push_back(common);
    for (int i = 0; i < uncommonWeight; i++) selectionPool.push_back(uncommon);
    for (int i = 0; i < rareWeight; i++) selectionPool.push_back(rare);
    for (int i = 0; i < epicWeight; i++) selectionPool.push_back(epic);
    for (int i = 0; i < legendaryWeight; i++) selectionPool.push_back(legendary);
    for (int i = 0; i < mythicWeight; i++) selectionPool.push_back(mythic);


    std::vector<rarity> result;
    for (int i = 0; i < 3; i++) {
        int index = std::rand() % selectionPool.size();
        result.push_back(selectionPool[index]);
    }

    return result;
}


static std::vector<upgrade> getRandomUpgrades() {
    std::vector<upgrade> selectionPool;

    for (int i = 0; i < attackSpeedWeight; i++) selectionPool.push_back(attackSpeed);
    for (int i = 0; i < speedWeight; i++) selectionPool.push_back(speed);
    for (int i = 0; i < penetrationWeight; i++) selectionPool.push_back(penetration);
    for (int i = 0; i < damageWeight; i++) selectionPool.push_back(damage);

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

static float getModifier(rarity rarity) {
    switch (rarity) {
    case common:
        return commonModifier;
    case uncommon:
        return uncommonModifier;
    case rare:
        return rareModifier;
    case epic:
        return epicModifier;
    case legendary:
        return legendaryModifier;
    case mythic:
        return mythicModifier;
    }
    return 1.0f;
};


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

static Color getColor(rarity rartiy) {
    switch (rartiy) {
    case common:
        return GRAY;
    case uncommon:
        return GREEN;
    case rare:
        return BLUE;
    case epic:
        return PURPLE;
    case legendary:
        return GOLD;
    case mythic:
        return RED;
    }
	return GRAY;
};

static Color getHoverColor(rarity rarity) {
    auto darken = [](unsigned char value, int amount) -> unsigned char {
        return static_cast<unsigned char>(std::max(0, value - amount));
        };

    switch (rarity) {
    case common:
        return { darken(GRAY.r, 30), darken(GRAY.g, 30), darken(GRAY.b, 30), GRAY.a };
    case uncommon:
        return { darken(GREEN.r, 40), darken(GREEN.g, 40), darken(GREEN.b, 40), GREEN.a };
    case rare:
        return { darken(BLUE.r, 40), darken(BLUE.g, 40), darken(BLUE.b, 40), BLUE.a };
    case epic:
        return { darken(PURPLE.r, 40), darken(PURPLE.g, 40), darken(PURPLE.b, 40), PURPLE.a };
    case legendary:
        return { darken(GOLD.r, 40), darken(GOLD.g, 40), darken(GOLD.b, 40), GOLD.a };
    case mythic:
        return { darken(RED.r, 40), darken(RED.g, 40), darken(RED.b, 40), RED.a };
    }
    return GRAY;
}

static void upgradeAttackSpeed(Player& player, float modifier) {
	player.attackSpeed *= (0.95f / modifier);
}

static void upgradeSpeed(Player& player, float modifier) {
	player.speed *= (1.03f * modifier);
}

static void upgradePenetration(Player& player, float modifier) {
    if (modifier == commonModifier || modifier == uncommonModifier) {
		player.penetration += 1;
	} else if(modifier == rareModifier || modifier == epicModifier) {
		player.penetration += 2;
	} else if(modifier == legendaryModifier || modifier == mythicModifier) {
		player.penetration += 3;
	}
}

static void upgradeDamage(Player& player, float modifier) {
	player.damage += (1 * modifier);
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

	Color color1 = getColor(rarities[0]);
	Color color2 = getColor(rarities[1]);
	Color color3 = getColor(rarities[2]);

	Color hoveredColor1 = getHoverColor(rarities[0]);
	Color hoveredColor2 = getHoverColor(rarities[1]);
	Color hoveredColor3 = getHoverColor(rarities[2]);

	float modifier1 = getModifier(rarities[0]);
	float modifier2 = getModifier(rarities[1]);
	float modifier3 = getModifier(rarities[2]);

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

            DrawRectangleRec(button1, hovered1 ? hoveredColor1 : color1);
            DrawRectangleLinesEx(button1, 3, BLACK);

            DrawRectangleRec(button2, hovered2 ? hoveredColor2 : color2);
            DrawRectangleLinesEx(button2, 3, BLACK);

            DrawRectangleRec(button3, hovered3 ? hoveredColor3 : color3);
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
			upgradeFunc1(player, modifier1);
            return true;
        }
        else if (hovered2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            upgradeFunc2(player, modifier2);
            return true;
        }
        else if (hovered3 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            upgradeFunc3(player, modifier3);
            return true;
        }
    };
    return false;
};

