#ifndef SELECTION_H
#define SELECTION_H
#include "Scene.h"
#include <sstream>

class Selection : public Scene {
private:
	std::stringstream ss;
public:
	Selection();
	void Update (Game & game)override;
	void Draw (sf::RenderWindow & w)override;
	void Player_Selection(Game &game);
	void Difficulty_Selection(int player, Game &game);
	void SetText();
	void SetText2();
	int PlayMusic()override;
};

#endif

