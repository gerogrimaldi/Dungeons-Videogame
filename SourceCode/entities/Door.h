#ifndef PUERTA_H
#define PUERTA_H
#include "entities/Enemy.h"
#include <SFML/Graphics/Color.hpp>
#include "Game.h"
#include "Player.h"

class Door : public Entity{
private:
	SoundBuffer buffer;
	Sound sound;
	Color color;
	bool already_appeared = false;
	bool already_opened = false;
public:
	Door();
	std::string Appear();
	bool Open(Game &game, bool has_key);
	bool ViewStatus();
	void RandomizePosition();
	sf::Vector2f ViewPosition();
};

#endif

