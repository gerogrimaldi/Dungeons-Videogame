#include "Key.h"
#include <cstdlib>
#include <iostream>

Key::Key() {
	e_texture.loadFromFile("images/key.png"); 
	e_sprite.setTexture(e_texture);
	
	//posicion de insercion
	this->RandomizePosition();
	
	//transparencia
	color = e_sprite.getColor(); 
	color.a=0; //que este oculto hasta que el jugador lo toca
	e_sprite.setColor(color);
	color.a=255; //ya guardo la transparencia para despues aplicarla
	
	//sonidos
	buffer.loadFromFile("audio/sfx/key_appear.ogg"); //cargo sfx
	sound.setBuffer(buffer);
	sound.setVolume(40.0);
	
	//tipo
	type = 0;
}

void Key::RandomizePosition(){
	//posicion de insercion
	int randX = (std::rand()%16);
	int randY = (std::rand()%12);
	float x = 40* randX;
	float y = 40* randY;
	
	//prevenir spawn sobre el jugador (0,0)
	while(x==0 and y==0){
		randX = (rand()%16);
		randY = (rand()%12);
		x = 40* randX;
		y = 40* randY;
	}
	e_sprite.setPosition(x,y);
	
	//para ver su spawn
//	std::cout << "Key pos: " << randX+1 << "  " << randY+1;
}

void Key::Appear(){
	//aplico transparencia y aparezco
	e_sprite.setColor(color);
	
	sound.stop();	
	sound.play();
	
	already_appeared = true;
}

bool Key::ViewStatus(){
	return already_appeared;
}

sf::Vector2f Key::ViewPosition(){
	return e_sprite.getPosition();
}
