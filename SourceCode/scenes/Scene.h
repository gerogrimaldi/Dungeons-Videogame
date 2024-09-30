#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Game;

class Scene {
private:
protected:
	sf::Font m_font;
	sf::Text m_t;
public:
	Scene();
	virtual void Update(Game &game) = 0;
	virtual void Draw(sf::RenderWindow &w) = 0;
	virtual int PlayMusic() = 0;
	virtual ~Scene(){}
};

#endif

