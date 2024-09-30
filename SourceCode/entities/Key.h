#ifndef KEY_H
#define KEY_H
#include "Entity.h"

class Key : public Entity {
private:
	SoundBuffer buffer;
	Sound sound;
	Color color;
	bool already_appeared = false;
public:
	Key();
	bool ViewStatus();
	void Appear();
	void RandomizePosition();
	sf::Vector2f ViewPosition();
};

#endif

