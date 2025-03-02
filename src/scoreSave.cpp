#include "scoreSave.h"

ScoreSaver::ScoreSaver(){
	std::ifstream file(fileName);
	if (file.is_open()) {
		file >> highScore;
		file.close();
	}
}

void ScoreSaver::saveHighScore(int score) {
	if (score > highScore) {
		highScore = score;
		std::ofstream file(fileName);
		file << highScore;
		file.close();
	}
}