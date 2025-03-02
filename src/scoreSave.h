#pragma once

#include <fstream>
#include <iostream>

class ScoreSaver {
	const char* fileName = "save/save.txt";
public:
	int highScore;
	ScoreSaver();

	void saveHighScore(int score);
};