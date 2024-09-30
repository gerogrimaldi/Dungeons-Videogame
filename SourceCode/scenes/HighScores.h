#ifndef FINAL_H
#define FINAL_H
#include "Scene.h"
#include <vector>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"
#include <fstream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <sstream>

struct Score{
	char name[4];
	int score = 0;
};

class HighScores : public Scene {
private:
	std::stringstream ss;
	std::vector<int> player_scores;
	std::vector<Score> high_scores;
	int difficulty, level;
	int total_score = 0;
	std::string file_name;
	bool compare = true;
	sf::Texture m_bg;
	sf::Sprite m_s;
public:
	HighScores(std::vector<int> scores, int dif, int levelx);
	void Update (Game &game)override;
	void Draw (sf::RenderWindow & w)override;
	void SetText(std::string str="");
	void ShowBestScores(std::string str="");
	void CalculateScore();
	void ReadFile();
	void CompareScore(Game &game);
	void SaveNewScore(int i, Game &game);
	void WriteFile();
	int PlayMusic()override;
	void ResetHighScores();
	~HighScores(){}
};

#endif

