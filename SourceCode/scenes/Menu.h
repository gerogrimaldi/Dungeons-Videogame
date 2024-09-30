#ifndef MENU_H
#define MENU_H
#include "Scene.h"
#include <SFML/Audio/Music.hpp>

class Menu : public Scene {
private:
	sf::Font m_font2;
	sf::Text m_t2;
	sf::Music *music = nullptr;
public:
	Menu();
	void Update(Game &game)override;
	void Draw(sf::RenderWindow &w)override;
	int PlayMusic()override;
	~Menu();
};

#endif

