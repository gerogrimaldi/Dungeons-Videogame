#include "Entity.h"
using namespace sf;

Entity::Entity(){}

void Entity::Draw(RenderWindow &w){
	w.draw(e_sprite); 
}

bool Entity::CollideWith(const Entity *E) const{
	auto r1 = this->e_sprite.getGlobalBounds();
	auto r2 = E->e_sprite.getGlobalBounds(); 
	return r1.intersects(r2);
}


