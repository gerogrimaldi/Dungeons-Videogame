#include "Knight.h"
#include <iostream>

Knight::Knight(){
	e_texture.loadFromFile("images/knight.png"); 
	e_sprite.setTexture(e_texture);
	//posicion de insercion
	e_sprite.setPosition(0,0); 
	//sfx de ataque y defensa
	buffer2.loadFromFile("audio/sfx/knight_attack.ogg");
	attack_SFX.setBuffer(buffer2);
	attack_SFX.setVolume(20.0);
	buffer3.loadFromFile("audio/sfx/knight_defend.ogg");
	defend_SFX.setBuffer(buffer3);
	defend_SFX.setVolume(40.0);
	//stats
	hp=300, ap=25;
	max_hp=hp, max_ap=ap;
	min_dmg=30, max_dmg=60; 
	attack_ap = 7, special_ap=10;
	hp_recover = 50, ap_recover = 7;
}

int Knight::SpecialAttack(){ //se cura, hace un tercio de daño y consume mitad de ap
	attack_SFX.play();
	
	int dmg;
	
	if(ap-special_ap>=0){ 
		
		dmg = min_dmg + rand()%max_dmg; 
		ap-=special_ap; 
		hp+=25;
		dmg = dmg/3;
		ss << "Atacas por: " << dmg;
		
		return dmg;
		
	}else{
		ss << "AP insuficiente! Daño reducido\n";
		dmg = min_dmg + rand()%max_dmg;
		dmg = dmg/3;
		ap-=1;
		
		ss << "Atacas por: " << dmg;
		return dmg; 
	}
}

void Knight::RestartInfo(){
	ss.clear();
	ss.str(""); //limpio stringstream
	
	ss << "Ingresa:\n\n";
	if (ap<attack_ap){
		ss << "1: Atacar (ap insuficiente)\n\n";
		ss << "2: Ataque con escudo (ap insuficiente)\n\n";
	}else{
		if(ap<special_ap){
			ss << "1: Atacar\n\n";
			ss << "2: Ataque con escudo (ap insuficiente)\n\n";
		}else{
			ss << "1: Atacar\n\n";
			ss << "2: Ataque con escudo\n\n";
		}
	}
	ss <<"3: Defenderse\n";
}

void Knight::Die(){
	this->SetDeath();
	e_texture.loadFromFile("images/death_img/knight_corpse.png");
	e_sprite.setTexture(e_texture);
}
