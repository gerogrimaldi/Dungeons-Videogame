#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <string>

using namespace sf;

class Entity {
private:

protected:
	Texture e_texture;
	Sprite e_sprite;
	int type;
public:
	Entity();
	void Draw(RenderWindow &w);
	bool CollideWith(const Entity *E) const;
	virtual ~Entity(){}
};

#endif

