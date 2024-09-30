#include "Orc.h"
#include <ctime>
using namespace std;

Orc::Orc() {
	//insercion
	e_texture.loadFromFile("images/orc.png");
	e_sprite.setTexture(e_texture);
	type = 3;
	//nombre
	name = "Orco";

	//transparencia
	color = e_sprite.getColor(); 
	color.a=0; //que este oculto hasta que el jugador lo toca
	e_sprite.setColor(color);
	color.a=255; //ya guardo la transparencia para despues aplicarla
	
	//stats
	hp=300; ap=25; 
	min_dmg=25, max_dmg=60;
	attack_ap = 8;
	hp_recover = 50, ap_recover = 10;
	//attack sfx
	buffer2.loadFromFile("audio/sfx/orc_attack.ogg");
	attack_sfx.setBuffer(buffer2);
	attack_sfx.setVolume(30.0);
	
}

void Orc::Appear(){
	//aplico transparencia y aparezco
	e_sprite.setColor(color);
	
	//sonidos
	buffer.loadFromFile("audio/sfx/orc_growl.ogg");
	sound.setBuffer(buffer);
	sound.setVolume(40.0);
	sound.stop();
	sound.play();
	
	this->SetAppeared();
}

void Orc::Die(){
	this->hp=0;
	//acomodo posicion
	e_sprite.setPosition(position);
	e_sprite.setScale(scale);
	//muerto
	IsAlive = false;
	//sfx de muerte
	buffer.loadFromFile("audio/sfx/orc_death.ogg");
	sound.setBuffer(buffer);
	sound.setVolume(40.0);
	sound.stop();
	sound.play();
}
