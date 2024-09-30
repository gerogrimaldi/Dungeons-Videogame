#include "Door.h"
#include <iostream>
//time manager
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
	#define Sleep(x) usleep((x)*1000)
#endif
//
#include "../scenes/HighScores.h"

Door::Door() {
	//insercion
	e_texture.loadFromFile("images/door.png");
	e_sprite.setTexture(e_texture);
	
	//posicion
	this->RandomizePosition();	
	
	//transparencia
	color = e_sprite.getColor(); 
	color.a=0; //que este oculto hasta que el jugador lo toca
	e_sprite.setColor(color);
	color.a=255; //ya guardo la transparencia para despues aplicarla

	//sonidos
	buffer.loadFromFile("audio/sfx/door_closed.ogg"); //cargo sfx
	sound.setBuffer(buffer);
	sound.setVolume(40.0);
	
	//tipo
	type = 1;
}

void Door::RandomizePosition(){
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
//	std::cout << "Door pos: " << randX+1 << "  " << randY+1;
}
std::string Door::Appear(){
	//aplico transparencia y aparezco
	e_sprite.setColor(color);

	sound.stop();	
	sound.play();
	
	already_appeared = true;

	return ("Has encontrado la salida!, pero esta cerrada con llave...");
}

bool Door::Open(Game &game, bool has_key){
	
	if(has_key){
		//sonidos
		buffer.loadFromFile("audio/sfx/door_open.ogg"); //cargo sfx
		sound.setBuffer(buffer);
		sound.setVolume(40.0);
		sound.stop();	
		sound.play();
		
		//imagen
		e_texture.loadFromFile("images/door_open.png");
		e_sprite.setTexture(e_texture);
		
		//draw open door sprite
		game.Draw();
		Sleep(2000);
		
		return true;
	}
	return false;
}
bool Door::ViewStatus(){
	return this->already_appeared;
}

sf::Vector2f Door::ViewPosition(){
	return e_sprite.getPosition();
}
