#include "Skeleton.h"
#include <ctime>
using namespace std;

Skeleton::Skeleton() {
	//insercion
	e_texture.loadFromFile("images/skeleton.png");
	e_sprite.setTexture(e_texture);
	type = 2;
	//nombre
	name = "Esqueleto";
	
	//transparencia
	color = e_sprite.getColor(); 
	color.a=0; //que este oculto hasta que el jugador lo toca
	e_sprite.setColor(color);
	color.a=255; //ya guardo la transparencia para despues aplicarla
	
	//stats
	hp=100, ap=75; 
	min_dmg=10, max_dmg=30;
	attack_ap = 15;
	hp_recover = 30, ap_recover = 30;
	
	//attack sfx
	buffer2.loadFromFile("audio/sfx/skeleton_attack.ogg");
	attack_sfx.setBuffer(buffer2);
	attack_sfx.setVolume(30.0);
}

void Skeleton::Appear(){
	//aplico transparencia y aparezco
	e_sprite.setColor(color);
	
	//sonidos
	buffer.loadFromFile("audio/sfx/skeleton_sfx.flac"); //cargo sfx
	sound.setBuffer(buffer);
	sound.setVolume(40.0);
	sound.stop();	
	sound.play();
	
	this->SetAppeared();
}

void Skeleton::Die(){
	this->hp=0;
	//acomodo posicion
	e_sprite.setPosition(position);
	e_sprite.setScale(scale);
	//muerto
	IsAlive = false;
	//sfx de muerte
	buffer.loadFromFile("audio/sfx/skeleton_death.ogg"); //una vez q muere reemplazo el sfx
	sound.setBuffer(buffer);
	sound.setVolume(20.0);
	sound.stop();	
	sound.play();
}
