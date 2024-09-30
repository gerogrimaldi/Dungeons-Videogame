#include "Pumpkin_Knight.h"
#include <ctime>
using namespace std;

Pumpkin_Knight::Pumpkin_Knight() {
	//insercion
	e_texture.loadFromFile("images/pumpkin_knight.png");
	e_sprite.setTexture(e_texture);
	type = 4;
	//nombre
	name = "Caballero calabaza";
	
	//transparencia
	color = e_sprite.getColor(); 
	color.a=0; //que este oculto hasta que el jugador lo toca
	e_sprite.setColor(color);
	color.a=255; //ya guardo la transparencia para despues aplicarla
	
	
	//stats
	hp=200; ap=50; 
	min_dmg=50, max_dmg=120;
	attack_ap = 12;
	hp_recover = 60, ap_recover = 15;

	//attack sfx
	buffer2.loadFromFile("audio/sfx/pumpkin_attack.ogg");
	attack_sfx.setBuffer(buffer2);
	attack_sfx.setVolume(30.0);
}

void Pumpkin_Knight::Appear(){
	//aplico transparencia y aparezco
	e_sprite.setColor(color);
	
	
	//sonidos
	buffer.loadFromFile("audio/sfx/pumpkin_laugh.ogg");
	sound.setBuffer(buffer);
	sound.setVolume(10.0);
	sound.stop();
	sound.play();
	
	this->SetAppeared();
}

void Pumpkin_Knight::Die(){
	this->hp=0;
	//acomodo posicion
	e_sprite.setPosition(position);
	e_sprite.setScale(scale);
	//muerto
	IsAlive = false;
	//sfx de muerte
	buffer.loadFromFile("audio/sfx/pumpkin_death.ogg");
	sound.setBuffer(buffer);
	sound.setVolume(30.0);
	sound.stop();
	sound.play();
}
