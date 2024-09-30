#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "Scene.h"

class Instructions : public Scene {
private:
public:
	Instructions();
	void Update (Game & game)override;
	void Draw (sf::RenderWindow & w)override;
	int PlayMusic()override;
	void SetText();
};

#endif

